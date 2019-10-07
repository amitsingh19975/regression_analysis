#include "./include/statistics.h"
#include <gsl/gsl_vector.h>

double stats_correlation(gsl_matrix *mat, size_t r1, size_t r2) {
    gsl_vector* data1 = gsl_vector_alloc(mat->size1);
    gsl_vector* data2 = gsl_vector_alloc(mat->size1);
    gsl_matrix_get_col(data1, mat, r1);
    gsl_matrix_get_col(data2, mat, r2);
    double corr = gsl_stats_correlation(data1 -> data, 1, data2 -> data, 1, data1 -> size);
    gsl_vector_free(data1);
    gsl_vector_free(data2);
    return corr;
}

double stats_spearman(gsl_matrix *mat, size_t r1, size_t r2) {
    gsl_vector* data1 = gsl_vector_alloc(mat->size1);
    gsl_vector* data2 = gsl_vector_alloc(mat->size1);
    gsl_matrix_get_col(data1, mat, r1);
    gsl_matrix_get_col(data2, mat, r2);
    double *work = (double *)malloc((data1 -> size) * 2 * sizeof(double));
    double corr = gsl_stats_spearman(data1 -> data, 1, data2 -> data, 1, data1 -> size, work);
    gsl_vector_free(data1);
    gsl_vector_free(data2);
    free(work);
    return corr;
}

double stats_autocorrelation(gsl_matrix *mat, size_t r) {
    gsl_vector* data = gsl_vector_alloc(mat->size1);
    gsl_matrix_get_col(data, mat, r);
    double ac = gsl_stats_lag1_autocorrelation(data -> data, 1, data -> size);
    gsl_vector_free(data);
    return ac;
}

double stats_covariance(gsl_matrix *mat, size_t r1, size_t r2) {
    gsl_vector* data1 = gsl_vector_alloc(mat->size1);
    gsl_vector* data2 = gsl_vector_alloc(mat->size1);
    gsl_matrix_get_col(data1, mat, r1);
    gsl_matrix_get_col(data2, mat, r2);
    double cov = gsl_stats_covariance(data1 -> data, 1, data2 -> data, 1, data1 -> size);
    gsl_vector_free(data1);
    gsl_vector_free(data2);
    return cov;
    
}
double stats_covariance_m(gsl_matrix *mat, size_t r1, size_t r2, double mean1, double mean2) {
    gsl_vector* data1 = gsl_vector_alloc(mat->size1);
    gsl_vector* data2 = gsl_vector_alloc(mat->size1);
    gsl_matrix_get_col(data1, mat, r1);
    gsl_matrix_get_col(data2, mat, r2);
    double cov = gsl_stats_covariance_m(data1 -> data, 1, data2 -> data, 1, data1 -> size, mean1, mean2);
    gsl_vector_free(data1);
    gsl_vector_free(data2);
    return cov;
}
