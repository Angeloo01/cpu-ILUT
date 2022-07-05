// Author: Angelo Gonzales
// Date: June 2022
#include "dense_LU.hpp"
#include "string.h"

#ifndef NDEBUG
#include "debug.hpp"
#endif

template<typename I, typename J>
int dense_LU_template(I m, J* matrix)
{
    if(m < 0)
    {
        return 1;
    }

    if(matrix == nullptr)
    {
        return 2;
    }

    if(m == 0)
    {
        return 0;
    }

    // for each row
    for(I i = 1; i < m; i++)
    {
        // for each column in row i under the diagonal
        for(I k = 0; k < i; k++)
        {
            // get the coefficient to perform row(i) = row(i) - pivot * row(k)
            J pivot = matrix[m * i + k] / matrix[m * k + k];

            // put pivot in lower matrix
            matrix[m * i + k] = pivot;

            // subtract row(k) from row(i)
            for(I j = k+1; j < m; j++)
            {
                matrix[m * i + j] = matrix[m * i + j] - pivot * matrix[m * k + j];
            }
        }
    }

    return 0;
}

extern int dense_LU(int m, float* matrixA)
{                                                                                             
    return dense_LU_template(m, matrixA);
}