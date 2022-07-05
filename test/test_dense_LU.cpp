#include "ilut_functions.h"
#include "debug.hpp"

void test_dense()
{
    static constexpr int m = 5;
    float matA[m*m] = {1, 1, 1, 1, 1,
                       1, 2, 1, 1, 1,
                       2, 3, 3, 1, 1,
                       3, 4, 5, 4, 1,
                       4, 5, 6, 7, 5};

    dense_LU(m, matA); 
    print_dense(m, m, matA);
}

void test_sparse()
{
    static constexpr int m = 5;
    float matA[m*m] = {1, 1, 0, 0, 1,
                       0, 2, 1, 0, 0,
                       0, 0, 3, 0, 0,
                       3, 0, 0, 4, 1,
                       4, 0, 6, 0, 5};
    // float matA[m*m] =    {1, 1,       1,
    //                          2, 1,     
    //                             3,  
    //                       3,       4, 1,
    //                             6,    5};

    dense_LU(m, matA);  
    print_dense(m, m, matA);
}

int main()
{
    test_dense();
    test_sparse();
    return 0;
}