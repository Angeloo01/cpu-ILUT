#include "debug.hpp"
#include "sparseio.hpp"
#include <fstream>

int main()
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
    

    return 0;
}