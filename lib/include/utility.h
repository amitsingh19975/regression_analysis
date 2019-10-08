#ifndef UTILITY_H
#define UTILITY_H
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_vector.h>
#include<stdio.h>
#endif

void print_matrix(FILE*,const gsl_matrix*);
void print_vector(FILE*,const gsl_vector*);