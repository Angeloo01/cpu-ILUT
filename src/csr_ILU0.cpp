// Author: Angelo Gonzales
// Date: June 2022
#include "csr_ILU0.hpp"
#include "string.h"

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

template<typename I, typename J, typename K>
int csr_ILU0_template(I m, K nnz, J* __restrict__ csr_val, const K* __restrict__ csr_ptr, const I* __restrict__ csr_col_ind)
{
    if(m < 0 || nnz < 0)
    {
        return 1;
    }

    if(nnz > 0 && (csr_val == nullptr || csr_col_ind == nullptr))
    {
        return 2;
    }

    if(m > 0 && csr_ptr == nullptr)
    {
        return 2;
    }

    if(m == 0 || nnz == 0)
    {
        return 0;
    }

    J* temp_buffer = new J[m];

    // for each row
    for(I i = 1; i < m; i++)
    {
        // copy row to working buffer
        memset(temp_buffer, 0, sizeof(J) * m);
        for(K c = csr_ptr[i]; c < csr_ptr[i+1]; c++)
        {
            temp_buffer[csr_col_ind[c]] = csr_val[c];
        }

        // for each column in row i under the diagonal
        for(I k = 0; k < i; k++)
        {
            if(temp_buffer[k] == 0)
            {
                continue;
            }

            //find the index of element k, k
            I pivot_index = find_index(csr_col_ind, csr_ptr[k], csr_ptr[k+1], k);
            if(pivot_index < 0)
            {
                delete[] temp_buffer;
                return 3; // if zero pivot, then matrix is invalid
            }

            // get the coefficient to perform row(i) = row(i) - pivot * row(k)
            // pivot = elm(i, k) / elm(k, k)
            J pivot = temp_buffer[k] / csr_val[pivot_index];

            // put pivot in lower matrix; put in elm(i, k)
            temp_buffer[k] = pivot;

            // subtract row(k) from row(i); perform row(i) = row(i) - pivot * row(k)
            // for each non-zero element in row k after column k
            for(K subtrahend_index = pivot_index + 1; subtrahend_index < csr_ptr[k+1]; subtrahend_index++)
            {
                // elm(i, j) = elm(i, j) - pivot * elm(k, j)
                I j = csr_col_ind[subtrahend_index];
                temp_buffer[j] = temp_buffer[j] - pivot * csr_val[subtrahend_index];
            }
        }

        // save working buffer to row
        for(K c = csr_ptr[i]; c < csr_ptr[i+1]; c++)
        {
            csr_val[c] = temp_buffer[csr_col_ind[c]];
        }
    }

    delete[] temp_buffer;

    return 0;
}

extern int csr_ILU0(int m, 
                    int nnz, 
                    float* __restrict__ csr_val, 
                    const int* __restrict__ csr_ptr, 
                    const int* __restrict__ csr_col_ind)
{                                                                                             
    return csr_ILU0_template(m, nnz, csr_val, csr_ptr, csr_col_ind);
}