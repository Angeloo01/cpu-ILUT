// Author: Angelo Gonzales
// Date: July 2022

#pragma once

#include <fstream>

namespace sparse
{
    int fscanf(std::ifstream& file, const char* formant, ...);
}