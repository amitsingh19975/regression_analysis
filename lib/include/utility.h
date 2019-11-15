#ifndef UTILITY_H
#define UTILITY_H
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_vector.h>
#include<stdio.h>

gsl_matrix * matrix_file(const char* file);

// Submatrix from a matrix
gsl_matrix *matrix_submatrix(gsl_matrix *mat, size_t r1, size_t r2);

#endif