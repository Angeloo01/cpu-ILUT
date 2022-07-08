#include "ilut_functions.h"
#include "debug.hpp"

void test_dense_csr()
{
    static constexpr int m = 5;
    static constexpr int nnz = m*m;
    float csr_val[nnz] = {1, 1, 1, 1, 1,
                          1, 2, 1, 1, 1,
                          2, 3, 3, 1, 1,
                          3, 4, 5, 4, 1,
                          4, 5, 6, 7, 5};
    int csr_ptr[m+1] = {0, 5, 10, 15, 20, 25};
    int csr_col_ind[nnz] = {0, 1, 2, 3, 4,
                            0, 1, 2, 3, 4,
                            0, 1, 2, 3, 4,
                            0, 1, 2, 3, 4,
                            0, 1, 2, 3, 4};

    static constexpr int p = 2;
    static constexpr int h_nnz = (1 + 2 * p) * m - p * (p + 1);
    float csr_val_B[h_nnz];
    int csr_ptr_B[m+1];
    int csr_col_ind_B[h_nnz];

    printNV(csr_ILUT(m, nnz, .1, p, csr_val, csr_ptr, csr_col_ind, csr_val_B, csr_ptr_B, csr_col_ind_B)); 
    print_array("val", csr_ptr_B[m], csr_val_B);
    print_array("col", csr_ptr_B[m], csr_col_ind_B);
    print_array("ptr", m+1, csr_ptr_B);
    print_unsorted_csr_matrix(csr_ptr_B[m], m, m, csr_val_B, csr_col_ind_B, csr_ptr_B);
}

void test_sparse_csr()
{
    static constexpr int m = 5;
    static constexpr int nnz = 12;
    float csr_val[nnz] = {1, 1,       1,
                             2, 1,     
                                3,  
                          3,       4, 1,
                          4,    6,    5};
    int csr_ptr[m+1] = {0, 3, 5, 6, 9, 12};
    int csr_col_ind[nnz] = {0, 1,       4,
                               1, 2,  
                                  2,  
                            0,       3, 4,
                            0,     2,    4};

    static constexpr int p = 1;
    static constexpr int h_nnz = (1 + 2 * p) * m - p * (p + 1);
    float csr_val_B[h_nnz];
    int csr_ptr_B[m+1];
    int csr_col_ind_B[h_nnz];

    csr_ILUT(m, nnz, 0.1, p, csr_val, csr_ptr, csr_col_ind, csr_val_B, csr_ptr_B, csr_col_ind_B); 
    print_array("val", csr_ptr_B[m], csr_val_B);
    print_array("col", csr_ptr_B[m], csr_col_ind_B);
    print_array("ptr", m+1, csr_ptr_B);
    print_unsorted_csr_matrix(csr_ptr_B[m], m, m, csr_val_B, csr_col_ind_B, csr_ptr_B);
}

int main()
{
    test_dense_csr();
    test_sparse_csr();
    return 0;
}