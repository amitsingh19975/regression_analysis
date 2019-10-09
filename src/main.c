#include <stdio.h>
#include <stdlib.h>
#include "../lib/include/exception.h"
#include "../lib/include/string.h"
#include "../lib/include/statistics.h"
#include "../lib/include/utility.h"
<<<<<<< HEAD
#include "../lib/include/csv_parser.h"
#include<time.h>


int main(int argc, char const *argv[])
{	
	INIT_EXCEPTION;
	const char* f = "/home/amit/Desktop/cancer_reg.csv";
	csv_frame* t = parse_csv(f);
	
	write_gsl_matrix("/tmp/gsl_matrix.data",t,3,0,1,2);
	delete_cframe(t);	
	CLEAN_EXCEPTION;
=======
#include "../lib/include/regression.h"
int main(int argc, char const *argv[])
{
    const char* filename = "./testData/data1";
    FILE *fptr = fopen(filename, "r");
    size_t nData, observations;
    fscanf(fptr, "%ld", &nData);
    fscanf(fptr, "%ld", &observations);
    gsl_matrix *mat = gsl_matrix_alloc(observations, nData);
    gsl_matrix_fscanf(fptr, mat);
    printf("Data set: \n");
    print_matrix(stdout, mat);
    gsl_vector *coff;
    gsl_matrix *cov;
    coff = gsl_vector_calloc((mat -> size2));
    cov = gsl_matrix_calloc((mat -> size2), (mat -> size2));
    double chisq;
    reg_ols_linear_fit(mat, coff, cov, &chisq);
    printf("Coff: ");
    print_vector(stdout, coff);
    printf("Covariance: \n");
    print_matrix(stdout, cov);
    printf("Chi squared: %g\n", chisq);
    printf("R-squared: %g\n", reg_ols_linear_rsq(mat, chisq));
    gsl_vector *regressand = gsl_vector_alloc(mat -> size1);
    gsl_matrix_get_col(regressand, mat, 1);
    printf("Central square sum: %g\n", stats_centralized_tss(regressand));
    printf("Square sum: %g\n", stats_tss(regressand));
    gsl_vector_free(regressand);
    gsl_vector_free(coff);
    gsl_matrix_free(cov);
    gsl_matrix_free(mat);
    fclose(fptr);
>>>>>>> stats
    return 0;
}
