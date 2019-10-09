#ifndef STATISTIC_H
#define STATISTIC_H
#include<gsl/gsl_statistics.h>
#include<gsl/gsl_matrix.h>
double stats_correlation(gsl_matrix *mat, size_t r1, size_t r2);
double stats_spearman(gsl_matrix *mat, size_t r1, size_t r2);
double stats_autocorrelation(gsl_matrix *mat, size_t r);
double stats_covariance(gsl_matrix *mat, size_t r1, size_t r2);
double stats_covariance_m(gsl_matrix *mat, size_t r1, size_t r2, double mean1, double mean2);
double stats_centralized_tss(gsl_vector *vec);
double stats_tss(gsl_vector* vec);
#endif