#include "./include/regression.h"
#include "./include/utility.h"
#include "./include/statistics.h"

int reg_ols_linear_fit(gsl_matrix *mat, gsl_vector *coff, gsl_matrix *cov, double *sumsq) {
    size_t params = (mat -> size2);
    size_t obs = mat -> size1;
    int status;
    gsl_vector_const_view regressand = gsl_matrix_const_column(mat, 0);
    gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc(obs, params);
    gsl_matrix *regressor = gsl_matrix_alloc(obs, params);
    gsl_matrix_memcpy(regressor, mat);
    gsl_vector *ones = gsl_vector_alloc(obs);
    gsl_vector_set_all(ones, 1);
    gsl_matrix_set_col(regressor, 0, ones);
    gsl_vector_free(ones);
    status = gsl_multifit_linear(regressor, &regressand.vector, coff, cov, sumsq, work);
    gsl_multifit_linear_free(work);
    return status;
}

double reg_ols_linear_rsq(gsl_matrix *mat,const double chisq) {
    gsl_vector_const_view regressand = gsl_matrix_const_column(mat, 0);
    double tss = stats_tss(&(regressand.vector));
    return (1. - (chisq / tss));
}

double reg_ols_linear_adj_rsq(gsl_matrix *mat, const double chisq) {
    gsl_vector_const_view regressand = gsl_matrix_const_column(mat, 0);
    double tss = stats_tss(&(regressand.vector));
    size_t obs = mat -> size1;
    size_t k = (mat -> size2) - 1;
    tss = tss / (obs - 1);
    double adj_chi = chisq / (obs - k);
    return (1. - (adj_chi / tss));
}

double 