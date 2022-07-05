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

template<typename I, typename J, typename K>
void print_csr_matrix(K nnz, I m, I n, const J* AA, const I* JA, const K* IA)
{
    //IA is size m+1
    for(I i = 0; i < m; i++){
        //iterate through each row; check if j is less than array size just in case
        I k = 0;
        for(K j = IA[i]; j < IA[i+1] && j < nnz; j++){
            //print 0 until non-zero value column
            for(; k < JA[j]; k++){
                std::cout << 0 << " ";
            }
            //print non-zero value
            std::cout << AA[j] << " ";
            k++;
        }
        //print remaining 0 if any
        for(; k < n; k++){
            std::cout << 0 << " ";
        }
        std::cout << std::endl;
    }
}

#endif