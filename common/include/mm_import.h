#pragma once

/* Reads coo array from filename and saves data in parameters
*  Returns:
*   -1 : error has occured/invalid file name
*    0 : successful
*    1 : invalid arguments
*    2 : file is an invalid matrix market format
*    3 : matrix is not supported
*
*/
int mm_coo_import_real(const char* filename, int& nnz, int& m, int& n, int index_base, float*& val, int*& row, int*& col);
int mm_coo_import_real(const char* filename, int& nnz, int& m, int& n, int index_base, double*& val, int*& row, int*& col);