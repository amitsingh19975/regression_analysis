#ifndef REGRESSION_H
#define REGRESSION_H
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_multifit.h>
#include<gsl/gsl_randist.h>
#include <math.h>

typedef struct OLS_data 
{
    gsl_vector *coefficient;
    gsl_matrix *covariance;
    double sum_sqrd_resid;
    gsl_vector *std_error;
    gsl_vector *t_ratio;
    gsl_vector *p_value;
} ols_data;


int reg_ols_linear_fit(gsl_matrix *mat, gsl_vector *coff, gsl_matrix *cov, double *sumsq);
ols_data reg_ols_linear_get_data(gsl_vector *coff, gsl_matrix *cov, double chisq, double df);
double reg_ols_linear_rsq(gsl_matrix *mat,const double sumsq);

#endif
