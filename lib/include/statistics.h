#ifndef STATISTIC_H
#define STATISTIC_H
#include<gsl/gsl_statistics.h>
#include<gsl/gsl_matrix.h>
double stats_correlation(gsl_matrix *mat, size_t c1, size_t c2);
double stats_spearman(gsl_matrix *mat, size_t c1, size_t c2);
double stats_rsum(gsl_matrix *mat, size_t r);
double stats_csum(gsl_matrix *mat, size_t c);
double stats_mean(gsl_matrix *mat, size_t c);
double stats_variance(gsl_matrix *mat, size_t c);
double stats_sd(gsl_matrix *mat, size_t c);
double stats_autocorrelation(gsl_matrix *mat, size_t c);
double stats_covariance(gsl_matrix *mat, size_t c1, size_t c2);
double stats_covariance_m(gsl_matrix *mat, size_t c1, size_t c2, double mean1, double mean2);
double stats_centralized_tss(gsl_matrix *mat, size_t c);
double stats_tss(gsl_matrix *mat, size_t c);
#endif
