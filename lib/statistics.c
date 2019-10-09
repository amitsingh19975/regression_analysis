#include "./include/statistics.h"
#include <gsl/gsl_vector.h>

double stats_correlation(gsl_matrix *mat, size_t c1, size_t c2) {
    gsl_vector* data1 = gsl_vector_alloc(mat->size1);
    gsl_vector* data2 = gsl_vector_alloc(mat->size1);
    gsl_matrix_get_col(data1, mat, c1);
    gsl_matrix_get_col(data2, mat, c2);
    double corr = gsl_stats_correlation(data1 -> data, 1, data2 -> data, 1, data1 -> size);
    gsl_vector_free(data1);
    gsl_vector_free(data2);
    return corr;
}

double stats_spearman(gsl_matrix *mat, size_t c1, size_t c2) {
    gsl_vector* data1 = gsl_vector_alloc(mat->size1);
    gsl_vector* data2 = gsl_vector_alloc(mat->size1);
    gsl_matrix_get_col(data1, mat, c1);
    gsl_matrix_get_col(data2, mat, c2);
    double *work = (double *)malloc((data1 -> size) * 2 * sizeof(double));
    double corr = gsl_stats_spearman(data1 -> data, 1, data2 -> data, 1, data1 -> size, work);
    gsl_vector_free(data1);
    gsl_vector_free(data2);
    free(work);
    return corr;
}

double stats_rsum(gsl_matrix *mat, size_t r) {
    gsl_vector *row = gsl_vector_alloc(mat -> size2);
    gsl_matrix_get_row(row, mat, r);
    double sum = 0;
    for (size_t i = 0; i < row -> size; i++)
    {
        sum += gsl_vector_get(row, i);
    }
    return sum;
}
double stats_csum(gsl_matrix *mat, size_t c) {
    gsl_vector *col = gsl_vector_alloc(mat -> size1);
    gsl_matrix_get_col(col, mat, c);
    double sum = 0;
    for (size_t i = 0; i < col -> size; i++)
    {
        sum += gsl_vector_get(col, i);
    }
    return sum;
}

double stats_mean(gsl_matrix *mat, size_t c) {
    gsl_vector *col = gsl_vector_alloc(mat -> size1);
    gsl_matrix_get_col(col, mat, c);
    return gsl_stats_mean(col -> data, 1, col -> size);
}

double stats_variance(gsl_matrix *mat, size_t c) {
    gsl_vector *col = gsl_vector_alloc(mat -> size1);
    gsl_matrix_get_col(col, mat, c);
    return gsl_stats_variance(col -> data, 1, col -> size);
}

double stats_sd(gsl_matrix *mat, size_t c) {
    gsl_vector *col = gsl_vector_alloc(mat -> size1);
    gsl_matrix_get_col(col, mat, c);
    return gsl_stats_sd(col -> data, 1, col -> size);
}

double stats_autocorrelation(gsl_matrix *mat, size_t c) {
    gsl_vector* data = gsl_vector_alloc(mat->size1);
    gsl_matrix_get_col(data, mat, c);
    double ac = gsl_stats_lag1_autocorrelation(data -> data, 1, data -> size);
    gsl_vector_free(data);
    return ac;
}

double stats_covariance(gsl_matrix *mat, size_t c1, size_t c2) {
    gsl_vector* data1 = gsl_vector_alloc(mat->size1);
    gsl_vector* data2 = gsl_vector_alloc(mat->size1);
    gsl_matrix_get_col(data1, mat, c1);
    gsl_matrix_get_col(data2, mat, c2);
    double cov = gsl_stats_covariance(data1 -> data, 1, data2 -> data, 1, data1 -> size);
    gsl_vector_free(data1);
    gsl_vector_free(data2);
    return cov;
    
}
double stats_covariance_m(gsl_matrix *mat, size_t c1, size_t c2, double mean1, double mean2) {
    gsl_vector* data1 = gsl_vector_alloc(mat->size1);
    gsl_vector* data2 = gsl_vector_alloc(mat->size1);
    gsl_matrix_get_col(data1, mat, c1);
    gsl_matrix_get_col(data2, mat, c2);
    double cov = gsl_stats_covariance_m(data1 -> data, 1, data2 -> data, 1, data1 -> size, mean1, mean2);
    gsl_vector_free(data1);
    gsl_vector_free(data2);
    return cov;
}

double stats_centralized_tss(gsl_matrix *mat, size_t c) {
    gsl_vector *vec = gsl_vector_alloc(mat -> size1);
    gsl_matrix_get_col(vec, mat, c);
    return gsl_stats_tss(vec -> data, 1, vec -> size);
}

double stats_tss(gsl_matrix* mat, size_t c) {
    gsl_vector *vec = gsl_vector_alloc(mat -> size1);
    gsl_matrix_get_col(vec, mat, c);
    int n = vec -> size;
    double sum = 0.;
    for (size_t i = 0; i < n; i++)
    {
        double val = gsl_vector_get(vec, i);
        sum += (val * val);
    }
    return sum;
}
