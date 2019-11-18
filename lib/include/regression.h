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
typedef struct 
{
    double mean_dependent_var;
    double sd_dependent_var;
    double se_regression;
    double r_sqrd;
    double adj_r_sqrd;
    double f;
    double p_value_f;
} ols_stats_data;

typedef struct
{
    gsl_vector *coefficient;
    gsl_matrix *covariance;
    double sum_sqrd_resid;
    gsl_vector *std_error;
    gsl_vector *t_ratio;
    gsl_vector *p_value;
    ols_stats_data stats;
} ols_data;


int reg_ols_linear_fit(gsl_matrix *mat, gsl_vector *coff, gsl_matrix *cov, double *sumsq);
ols_data reg_ols_linear_get_data(gsl_matrix *mat, gsl_vector *coff, gsl_matrix *cov, double chisq);
double reg_ols_linear_rsq(gsl_matrix *mat,const double sumsq);
int reg_ols_linear_predict(const gsl_vector *x, const gsl_vector *coff, const gsl_matrix *cov, double *y, double *y_err);

#endif
