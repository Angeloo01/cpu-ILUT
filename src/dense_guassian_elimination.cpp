// Author: Angelo Gonzales
// Date: June 2022
#include "dense_guassian_elimination.hpp"
#include "string.h"

#ifndef NDEBUG
#include "debug.hpp"
#endif

template<typename I, typename J>
int dense_guassian_elimination_template(I m, J* matA)
{
    if(m < 0)
    {
        return 1;
    }

    if(matA == nullptr)
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
            J pivot = matA[m * i + k] / matA[m * k + k];

            // subtract row(k) from row(i)
            for(I j = 0; j < m; j++)
            {
                matA[m * i + j] = matA[m * i + j] - pivot * matA[m * k + j];
            }
#ifndef NDEBUG
            print_dense(m, m, matA);
            std::cout << std::endl;
#endif
        }
    }

    return 0;
}

extern int dense_guassian_elimination(int m, float* matrixA)
{                                                                                             
    return dense_guassian_elimination_template(m, matrixA);
}