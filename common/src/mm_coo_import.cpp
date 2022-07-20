#include <stdio.h>
#include <stdlib.h>
#include "mmio.h"

template <typename T, typename I, typename J>
int mm_coo_import_real_template(const char* filename, I& nnz, J& m, J& n, J index_base, T*& val, J*& row, J*& col)
{
    MM_typecode matcode;
    FILE *f;

    if (filename == nullptr)
	{
		return 1;
	}
    else    
    { 
        if ((f = fopen(filename, "r")) == NULL) 
            return -1;
    }

    if (mm_read_banner(f, &matcode) != 0)
    {
        if (f !=stdin) fclose(f);
        return 2;
    }


    // Supports only real sparse matrices

    if (!mm_is_real(matcode) && !mm_is_matrix(matcode) && !mm_is_sparse(matcode))
    {
        if (f !=stdin) fclose(f);
        return 3;
    }

    // find size of sparse matrix

    if (mm_read_mtx_crd_size(f, &m, &n, &nnz) !=0)
    {
        if (f !=stdin) fclose(f);
        return 2;
    }



    val = new T[nnz];
    col = new J[nnz];
    row = new J[nnz];


    /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
    /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
    /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */

    for (I i=0; i<nnz; i++)
    {
        if(fscanf(f, "%d %d %lg\n", &row[i], &col[i], &val[i]) != 3)
        {
            if (f !=stdin) fclose(f);
            return 2;
        }
        row[i] += index_base - 1;
        col[i] += index_base - 1;
    }

    if (f !=stdin) fclose(f);

	return 0;
}

extern int mm_coo_import_real(const char* filename, int& nnz, int& m, int& n, int index_base, float*& val, int*& row, int*& col)
{
    mm_coo_import_real_template(filename, nnz, m, n, index_base, val, row, col);
}

extern int mm_coo_import_real(const char* filename, int& nnz, int& m, int& n, int index_base, double*& val, int*& row, int*& col)
{
    mm_coo_import_real_template(filename, nnz, m, n, index_base, val, row, col);
}