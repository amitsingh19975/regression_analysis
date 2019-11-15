#include"./include/utility.h"


gsl_matrix *matrix_file(const char *file) {
    FILE *fptr = fopen(file, "r");
    size_t obs, data_set;
    fscanf(fptr, "%ld", &data_set);
    fscanf(fptr, "%ld", &obs);
    gsl_matrix* mat = gsl_matrix_alloc(obs, data_set);
    gsl_matrix_fscanf(fptr, mat);
    fclose(fptr);
    return mat;
}

gsl_matrix *matrix_submatrix(gsl_matrix *mat, size_t r1, size_t r2) {
    
}
