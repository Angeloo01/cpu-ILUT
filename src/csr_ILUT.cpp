// Author: Angelo Gonzales
// Date: June 2022
#include "csr_ILUT.hpp"
#include "string.h"  // memx
#include <algorithm> // std::sort
#include <cmath>     // sqrt

#ifndef NDEBUG
#include "debug.hpp"
#endif

template<typename I, typename J>
I find_index(const I* arr, J low, J high, I key)
{   
    while(low < high)
    {
        J mid = (low + high) >> 1;

        if(key > arr[mid])
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }

    if(arr[low] == key)
    {
        return low;
    }
    else
    {
        return -1;
    }
}

template<typename J>
J abs_j(J val)
{   
    if(val < 0)
    {
        val = -val;
    }
    return val;
}

template<typename J>
J row_norm(const J* row_start, const J* row_end)
{   
    J sqr_sum = 0;
    for(const J* curr = row_start; curr < row_end; curr++)
    {
        sqr_sum += (*curr) * (*curr);
    }
    
    return sqrt(sqr_sum);
}

// returns size of row
template<typename I, typename J>
I build_lu_row_permutation(I m, I p, I k, J* row, I* permutation)
{   
    if(k > p)
    {
        // find p biggest elements on l side; O(m) on average
        std::nth_element(permutation, (permutation + p), (permutation + k), 
            [row](I a, I b){
                //prioritize elements closer to diagonal
                if(abs_j(row[a]) == abs_j(row[b]))
                {
                    return a > b;
                }
                return abs_j(row[a]) > abs_j(row[b]);
            }
        );
    }

    if((m - k - 1) > p)
    {
        // find p biggest elements on u side; O(m) on average
        std::nth_element((permutation + k + 1), (permutation + k + 1 + p), (permutation + m), 
            [row](I a, I b){
                //prioritize elements closer to diagonal
                if(abs_j(row[a]) == abs_j(row[b]))
                {
                    return a < b;
                }
                return abs_j(row[a]) > abs_j(row[b]);
            }
        );
    }

    // guard
    I end = (k + p + 1) < m ? (k + p + 1) : m;

    // compress
    if(k > p)
    {
        // std::shift_left((permutation + k), (permutation + end), (k - p));
        for(I i = 0; i < (end - k); i++)
        {
            I temp = permutation[p + i];
            permutation[p + i] = permutation[k + i];
            permutation[k + i] = temp;
        }

        return (p + end - k);
    }
    else
    {
        return end;
    }
}

template<typename I, typename J, typename K>
int csr_ILUT_template(I m, 
                      K nnz, 
                      J tau, 
                      I p, 
                      const J*   __restrict__ csr_val_A, 
                      const K*   __restrict__ csr_ptr_A, 
                      const I*   __restrict__ csr_col_ind_A, 
                      J*         __restrict__ csr_val_B, 
                      K*         __restrict__ csr_ptr_B, 
                      I*         __restrict__ csr_col_ind_B)
{
    if(m < 0 || nnz < 0 || p <= 0 || tau <= 0)
    {
        return 1;
    }

    if(nnz > 0 && (csr_val_A == nullptr || csr_col_ind_A == nullptr || csr_val_B == nullptr || csr_col_ind_B == nullptr))
    {
        return 2;
    }

    if(m > 0 && (csr_ptr_A == nullptr || csr_ptr_B == nullptr))
    {
        return 2;
    }

    if(m == 0 || nnz == 0)
    {
        return 0;
    }

    J r_tol = 0;

    J* temp_buffer = new J[m];
    I* temp_perm_buffer = new I[m]; // permutation is also column of each element
    K* temp_pivot_buffer = new K[m]; // holds the index of diagonal elements

    // initialize row ptr B
    csr_ptr_B[0] = 0;

    // for each row
    for(I i = 0; i < m; i++)
    {
        //calculate relative tolerance
        r_tol = tau * row_norm(&csr_val_A[csr_ptr_A[i]], &csr_val_A[csr_ptr_A[i+1]]);

        // replace
        // copy row to working buffer
        memset(temp_buffer, 0, sizeof(J) * m);

        for(K c = csr_ptr_A[i]; c < csr_ptr_A[i+1]; c++)
        {
            temp_buffer[csr_col_ind_A[c]] = csr_val_A[c];
        }

        // for each column in row i under the diagonal
        for(I k = 0; k < i; k++)
        {
            if(temp_buffer[k] == 0)
            {
                continue;
            }

            //find the index of element k, k in the upper matrix
            //K pivot_index = find_index(csr_col_ind_B, csr_ptr_B[k], csr_ptr_B[k+1], k);
            K pivot_index = temp_pivot_buffer[k];

            // get the coefficient to perform row(i) = row(i) - pivot * row(k)
            // pivot = elm(i, k) / elm(k, k)
            J pivot = temp_buffer[k] / csr_val_B[pivot_index];

            if(abs_j(pivot) >= r_tol)
            {
                // put pivot in lower matrix; put in elm(i, k)
                temp_buffer[k] = pivot;

                // subtract row(k) from row(i); perform row(i) = row(i) - pivot * row(k)
                // for each non-zero element in row k after column k
                for(K subtrahend_index = pivot_index + 1; subtrahend_index < csr_ptr_B[k+1]; subtrahend_index++)
                {
                    // elm(i, j) = elm(i, j) - pivot * elm(k, j)
                    I j = csr_col_ind_B[subtrahend_index];
                    temp_buffer[j] = temp_buffer[j] - pivot * csr_val_B[subtrahend_index];
                }
            }
            else
            {
                // drop element
                temp_buffer[k] = 0;
            }
        }

        // reset perm buffer
        for(I index = 0; index < m; index++)
        {
            temp_perm_buffer[index] = index;
        }

        // get largest p elements
        I row_size = build_lu_row_permutation(m, p, i, temp_buffer, temp_perm_buffer);
        I dropped_elements = 0;

        // save working buffer to row
        for(I c = 0; c < row_size; c++)
        {
            I col = temp_perm_buffer[c];

            //drop elements that are less than r_tol and not diagonal
            if(abs_j(temp_buffer[col]) >= r_tol || col == i)
            {
                csr_val_B[csr_ptr_B[i] + c - dropped_elements] = temp_buffer[col];
                csr_col_ind_B[csr_ptr_B[i] + c - dropped_elements] = col;

                if(col == i)
                {
                    temp_pivot_buffer[i] = csr_ptr_B[i] + c - dropped_elements;
                }
            }
            else
            {
                dropped_elements++;
            }
        }

        csr_ptr_B[i+1] = csr_ptr_B[i] + row_size - dropped_elements;
    }

    delete[] temp_buffer;
    delete[] temp_perm_buffer;
    delete[] temp_pivot_buffer;

    return 0;
}

extern int csr_ILUT(int m, 
                    int nnz, 
                    float tau, 
                    int p, 
                    const float* __restrict__ csr_val_A, 
                    const int*   __restrict__ csr_ptr_A, 
                    const int*   __restrict__ csr_col_ind_A, 
                    float*       __restrict__ csr_val_B, 
                    int*         __restrict__ csr_ptr_B, 
                    int*         __restrict__ csr_col_ind_B)
{                                                                                             
    return csr_ILUT_template(m, nnz, tau, p, csr_val_A, csr_ptr_A, csr_col_ind_A, csr_val_B, csr_ptr_B, csr_col_ind_B);
}