#include "./include/regression.h"
#include "./include/utility.h"
#include "./include/statistics.h"

/**
Provide with a p size vector to store cofficients and
p*p size matrix to store cov
a double that will store sum of square of residuals
p = mat -> size2
*/
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
    double tss = stats_tss(mat, 0);
    return (1. - (chisq / tss));
}

double reg_ols_linear_adj_rsq(gsl_matrix *mat, const double chisq) {
    gsl_vector_const_view regressand = gsl_matrix_const_column(mat, 0);
    double tss = stats_tss(mat, 0);
    size_t obs = mat -> size1;
    size_t k = (mat -> size2) - 1;
    tss = tss / (obs - 1);
    double adj_chi = chisq / (obs - k);
    return (1. - (adj_chi / tss));
}

ols_data reg_ols_linear_get_data(gsl_matrix *mat, gsl_vector *coff, gsl_matrix *cov, double chisq) {
    ols_data data;
    double df = (mat -> size1) - (mat -> size2);
    gsl_vector *std_error = gsl_vector_alloc(coff -> size);
    gsl_vector *t_ratio = gsl_vector_alloc(coff -> size);
    gsl_vector *p_value = gsl_vector_alloc(coff -> size);
    
    for (size_t i = 0; i < coff -> size; i++)
    {
        double se = sqrt( gsl_matrix_get( cov, i, i ) );
        gsl_vector_set( std_error, i, se );
        double t = gsl_vector_get( coff, i ) / se;
        gsl_vector_set( t_ratio, i, t );
        gsl_vector_set( p_value, i, gsl_ran_tdist_pdf( t, df ) );
    }

    data.coefficient = coff;
    data.covariance = cov;
    data.p_value = p_value;
    data.std_error = std_error;
    data.sum_sqrd_resid = chisq;
    data.t_ratio = t_ratio;


    ols_stats_data stats;
    double mean = stats_mean(mat, 0);
    double var = stats_variance(mat, 0);
    double sd = sqrt(var);
    double r_sqrd = reg_ols_linear_rsq(mat, chisq);
    double adj_r_sqrd = reg_ols_linear_adj_rsq(mat, chisq);

    double ssm = 0;
    for (size_t i = 0; i < mat -> size1; i++)
    {
        gsl_vector *x = gsl_vector_alloc(mat -> size2);
        gsl_matrix_get_row(x, mat, i);
        gsl_vector_set(x, 0, 1);
        double y, y_err;
        reg_ols_linear_predict(x, coff, cov, &y, &y_err);
        ssm += ((y - mean) * ( y- mean));
    }
    
    double msm = ssm / ((mat -> size2) - 1);
    double mse = chisq / df;
    double f = msm / mse;
    double p_value_f = gsl_ran_flat_pdf(f, (mat -> size2) - 1, df);

    stats.f = f;
    stats.p_value_f = p_value_f;
    stats.mean_dependent_var = mean;
    stats.sd_dependent_var = sd;
    stats.r_sqrd = r_sqrd;
    stats.adj_r_sqrd = adj_r_sqrd;
    data.stats = stats;
    return data;
    
}

int reg_ols_linear_predict(const gsl_vector *x, const gsl_vector *coff, const gsl_matrix *cov, double *y, double *y_err) {
    if ((x -> size) == (coff -> size) - 1) {
        gsl_vector *fixed_x = gsl_vector_alloc(coff -> size);
        for (size_t i = 0; i < x -> size; i++)
        {
            gsl_vector_set(fixed_x, i+1, gsl_vector_get(x, i));
        }
        gsl_vector_set(fixed_x, 0, 1);
        return gsl_multifit_linear_est(fixed_x, coff, cov, y, y_err);
    } else {
        return gsl_multifit_linear_est(x, coff, cov, y, y_err);
    }
}