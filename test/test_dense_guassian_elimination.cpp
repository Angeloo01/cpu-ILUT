#include "ilut_functions.h"
#include "debug.hpp"

int main()
{
    static constexpr int m = 5;
    float matA[m*m] = {1, 1, 1, 1, 1,
                       1, 2, 1, 1, 1,
                       2, 3, 3, 1, 1,
                       3, 4, 5, 4, 1,
                       4, 5, 6, 7, 5};

    dense_guassian_elimination(m, matA); 
    print_dense(m, m, matA);
    return 0;
}