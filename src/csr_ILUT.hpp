// Author: Angelo Gonzales
// Date: July 2022
#pragma once
#ifndef CSR_ILUT_H
#define CSR_ILUT_H

template<typename I, typename J, typename K>
int csr_ILUT_template(I m, 
                      K nnz, 
                      J tau, 
                      I p, 
                      const J*   __restrict__ csr_val_A, 
                      const K*   __restrict__ csr_ptr_A, 
                      const I*   __restrict__ csr_col_ind_A, 
                      J*         __restrict__ csr_val_B, 
                      K*         __restrict__ csr_ptr_B, 
                      I*         __restrict__ csr_col_ind_B);

#endif