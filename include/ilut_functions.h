// Author: Angelo Gonzales
// Date: June 2022
#pragma once
#ifndef ILUT_FUNCTIONS_H
#define ILUT_FUNCTIONS_H

int dense_guassian_elimination(int m, float* matrixA);

int dense_LU(int m, float* matrix);

int csr_ILU0(int m, 
             int nnz, 
             float*     __restrict__ csr_val, 
             const int* __restrict__ csr_ptr, 
             const int* __restrict__ csr_col_ind);

/* Assumptions:
*   - csr_val_A is of size nnz
*   - csr_ptr_A is of size m+1
*   - cst_col_ind_A is of size nnz
*
*   - csr_val_B is of size (1 + 2p)m - p(p + 1);
*   - csr_ptr_B is of size m+1
*   - cst_col_ind_B is of size (1 + 2p)m - p(p + 1);
*  
*/ 
int csr_ILUT(int m, 
             int nnz, 
             float tau, 
             int p, 
             const float* __restrict__ csr_val_A, 
             const int*   __restrict__ csr_ptr_A, 
             const int*   __restrict__ csr_col_ind_A, 
             float*       __restrict__ csr_val_B, 
             int*         __restrict__ csr_ptr_B, 
             int*         __restrict__ csr_col_ind_B);

#endif