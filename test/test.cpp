#include "debug.hpp"
#include "sparseio.hpp"
#include "mm_import.h"
#include <fstream>

void customRead()
{
    std::ifstream a("/home/cgy-decidueye/Repos/cpu-ILUT/test/tests/csr_ex.txt");
    
    if(a.is_open())
    {
        int m, nnzA, nnzR, p, *ptr, *col;
        float tau, *val;

        printNV(sparse::fscanf(a, "%d %d %d %f %d", &m, &nnzA, &nnzR, &tau, &p));

        printNV(m);
        printNV(nnzA);
        printNV(nnzR);
        printNV(tau);
        printNV(p);

        val = new float[nnzA];
        col = new int[nnzA];
        ptr = new int[m+1];

        printNV(sparse::fscanf(a, "%csr", m, nnzA, val, ptr, col));

        print_unsorted_csr_matrix(nnzA, m, m, val, col, ptr);

        printNV(sparse::fscanf(a, "%csr", m, nnzA, val, ptr, col));

        print_unsorted_csr_matrix(nnzA, m, m, val, col, ptr);

        delete[] val;
        delete[] col;
        delete[] ptr;

        a.close();
    }
}

void mm_import()
{
    const char* filename = "/home/cgy-decidueye/Repos/cpu-ILUT/test/tests/impcol_b.mtx";
    int m, n, nnz, *row, *col;
    double *val;

    printNV(mm_coo_import_real(filename, nnz, m, n, 1, val, row, col));
    printNV(nnz);
    printNV(m);
    printNV(n);
}

int main()
{
    mm_import();
    return 0;
}