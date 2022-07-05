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

    csr_ILU0(m, nnz, csr_val, csr_ptr, csr_col_ind); 
    print_csr_matrix(nnz, m, m, csr_val, csr_col_ind, csr_ptr);
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

    csr_ILU0(m, nnz, csr_val, csr_ptr, csr_col_ind); 
    print_csr_matrix(nnz, m, m, csr_val, csr_col_ind, csr_ptr);
}

int main()
{
    test_dense_csr();
    test_sparse_csr();
    return 0;
}