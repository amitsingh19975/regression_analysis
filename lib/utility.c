#include"./include/utility.h"

void print_matrix(FILE* file, gsl_matrix * mat) {
    for (size_t i = 0; i < mat->size1; i++)
    {
        for (size_t j = 0; j < mat->size2; j++)
        {
            fprintf(file, "%g\t", gsl_matrix_get(mat, i, j));
        }
        fprintf(file, "\n");
    }
}
void print_vector(FILE* file, gsl_vector * vec) {
    size_t i;
    for (i = 0; i < (vec -> size) - 1; i++)
    {
        fprintf(file, "%g, ", gsl_vector_get(vec, i));
    }
    fprintf(file, "%g\n", gsl_vector_get(vec, i));
}