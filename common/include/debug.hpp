// Author: Angelo Gonzales
// Date: June 2022
#pragma once
#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <assert.h>
#include <algorithm>
#include "string.h"

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

template<typename I, typename J, typename K>
void print_unsorted_csr_matrix(K nnz, I m, I n, const J* AA, const I* JA, const K* IA)
{
    J *temp_row = new J[n];

    //IA is size m+1
    for(I i = 0; i < m; i++){
        memset(temp_row, 0, sizeof(J) * n);
        for(K c = IA[i]; c < IA[i+1] && c < nnz; c++){
            temp_row[JA[c]] = AA[c];
        }
        for(I j = 0; j < n; j++)
        {
            std::cout << temp_row[j] << " ";
        }
        std::cout << std::endl;
    }

    delete[] temp_row;
}

template<typename I, typename J>
void print_array(I n, J* arr)
{
    std::cout << '[';
    for(I i = 0; i < n-1; i++)
    {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[n-1] << ']' << std::endl;
}

template<typename I, typename J>
void print_array(const char* name, I n, J* arr)
{
    std::cout << name << ": ";
    print_array(n, arr);
}

template<typename I, typename J, typename K>
int csrsort(const K nnz, const I m, const I n, 
                        const J* srcAA, const I* srcJA, const K* srcIA,
                        J* destAA, I* destJA, K* destIA)
{

    if(memcpy(destIA, srcIA, sizeof(I) * (m+1)) == nullptr){
        return -1;
    }

    I indeces[nnz];
    for(K i = 0; i < nnz; i++) indeces[i] = i;
    for(I i = 0; i < m; i++){
        std::sort(indeces + srcIA[i], indeces + srcIA[i+1], [srcJA](I a, I b){
            return srcJA[a] < srcJA[b];
        });
    }

    for(K i = 0; i < nnz; i++){
        destAA[i] = srcAA[indeces[i]];
        destJA[i] = srcJA[indeces[i]];
    }


    return 0;
}

template<typename I, typename J, typename K>
int csrsort(const K nnz, const I m, const I n, 
            J* destAA, I* destJA, K* destIA)
{

    J *tAA = new J[nnz];
    I *tJA = new I [nnz];
    K *tIA = new K [m+1];

    if(memcpy(tAA, destAA, sizeof(J) * (nnz)) == nullptr){
        return -1;
    }

    if(memcpy(tJA, destJA, sizeof(I) * (nnz)) == nullptr){
        return -1;
    }

    if(memcpy(tIA, destIA, sizeof(K) * (m+1)) == nullptr){
        return -1;
    }

    csrsort(nnz, m, n, tAA, tJA, tIA, destAA, destJA, destIA);

    delete[] tAA;
    delete[] tJA;
    delete[] tIA;

    return 0;
}

#endif