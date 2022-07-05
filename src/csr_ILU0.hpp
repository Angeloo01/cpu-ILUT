// Author: Angelo Gonzales
// Date: July 2022
#pragma once
#ifndef CSR_ILU0_H
#define CSR_ILU0_H

template<typename I, typename J, typename K>
int csr_ILU0_template(I m, K nnz, J* csr_val, K* csr_ptr, I* csr_col_ind);

#endif