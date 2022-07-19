// Author: Angelo Gonzales
// Date: July 2022

#include "../sparseio.hpp"
#include <regex>
#include <iostream>
#include <stdarg.h>
#include "debug.hpp"

int sparse::fscanf(std::ifstream& file, const char* format, ...)
{
    int count = 0;

    va_list args;
    va_start(args, format);

    const std::string s(format);
 
    std::regex words_regex("%([df]|(csr))");
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = std::sregex_iterator();
 
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;                                                 
        std::string match_str = match.str(); 

        count++;

        if(match_str.compare("%d") == 0)
        {
            int* var = va_arg(args, int*);
            file >> *var;
        }
        else if(match_str.compare("%f") == 0)
        {
            float* var = va_arg(args, float*);
            file >> *var;
        }
        else if(match_str.compare("%csr") == 0)
        {
            int    m   = va_arg(args, int);
            int    nnz = va_arg(args, int);
            float* val = va_arg(args, float*);
            int*   ptr = va_arg(args, int*);
            int*   ind = va_arg(args, int*);

            for(int i = 0; i < nnz && file.good(); i++)
            {
                file >> val[i];
            }

            for(int i = 0; i <= m && file.good(); i++)
            {
                file >> ptr[i];
            }

            for(int i = 0; i < nnz && file.good(); i++)
            {
                file >> ind[i];
            }
        }

        if(!file.good())
        {
            count--;
            break;
        }
    }  

    va_end(args); 

    return count;
}