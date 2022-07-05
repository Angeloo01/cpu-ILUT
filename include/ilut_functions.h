// Author: Angelo Gonzales
// Date: June 2022
#pragma once
#ifndef ILUT_FUNCTIONS_H
#define ILUT_FUNCTIONS_H

int dense_guassian_elimination(int m, float* matrixA);

int dense_LU(int m, float* matrix);

int csr_ILU0(int m, int nnz, float* csr_val, int* csr_ptr, int* csr_col_ind);

#endif