#ifndef REGRESSION_H
#define REGRESSION_H
#include<stdio.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_multifit.h>
#endif

int reg_ols_linear_fit(gsl_matrix *mat, gsl_vector *coff, gsl_matrix *cov, double *sumsq);
double reg_ols_linear_rsq(gsl_matrix *mat,const double sumsq);
