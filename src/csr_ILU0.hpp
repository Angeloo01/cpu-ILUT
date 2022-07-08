// Author: Angelo Gonzales
// Date: July 2022
#pragma once
#ifndef CSR_ILU0_H
#define CSR_ILU0_H

template<typename I, typename J, typename K>
int csr_ILU0_template(I m, K nnz, J* __restrict__ csr_val, const K* __restrict__ csr_ptr, const I* __restrict__ csr_col_ind);

#endif