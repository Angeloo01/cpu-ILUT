// Author: Angelo Gonzales
// Date: July 2022
#include "debug.hpp"

template<typename I, typename J>
bool array_compare(I* a, I* b, J n)
{
    for(J i = 0; i < n; i++)
    {
        if(a[i] != b[i])
        {
            printNV(i);
            printNV(a[i]);
            printNV(b[i]);
            return false;
        }
    }
    return true;
}

template<typename I, typename J>
bool array_compare(I* a, I* b, J n, I tol)
{
    tol = (tol >= 0) ? tol : -tol;
    for(J i = 0; i < n; i++)
    {
        if((a[i] - b[i]) < -tol || (a[i] - b[i]) > tol)
        {
            printNV(i);
            printNV(a[i]);
            printNV(b[i]);
            return false;
        }
    }
    return true;
}