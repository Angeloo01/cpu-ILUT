// Author: Angelo Gonzales
// Date: June 2022
#pragma once
#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <assert.h>

#define printNV(var) std::cout << #var": " << var << std::endl;

template<typename I, typename J>
void print_dense(I m, I n, J mat)
{
    for(I i = 0; i < m; i++)
    {
        for(I j = 0; j < m; j++)
        {
            std::cout << mat[n * i + j] << " ";
        }
        std::cout << std::endl;
    }
}

#endif