#include <stdio.h>
#include <stdlib.h>
#include "../lib/include/exception.h"
#include "../lib/include/string.h"
#include "../lib/include/statistics.h"
#include "../lib/include/utility.h"
#include "../lib/include/csv_parser.h"
#include "../lib/include/regression.h"
#include<time.h>
#include<math.h>
#include<gsl/gsl_randist.h>

int main(int argc, char const *argv[])
{	
	INIT_EXCEPTION;
	gsl_matrix * mat = matrix_file("../testData/data1");
	print_matrix(stdout, mat);
	printf("Tss of y: %g\n", stats_tss(mat, 0));
	gsl_vector *coff = gsl_vector_alloc(mat->size2);
	gsl_matrix *cov = gsl_matrix_alloc(mat -> size2, mat->size2);
	double chisq;
	int status = reg_ols_linear_fit(mat, coff, cov, &chisq);
	printf("Status: %d\n", status);
	puts("Cofficients");
	print_vector(stdout, coff);
	puts("Covariance Matrix: ");
	print_matrix(stdout, cov);
	puts("\n\n");
	double df = (mat->size1) - (mat->size2);
	printf("Σμ² =  %g\n", chisq);
	printf("σ̂² = %g\n", chisq / ((mat -> size1) - (mat -> size2)));
	puts("\n\n");
	ols_data data =  reg_ols_linear_get_data(coff, cov, chisq, df);
	puts("t-ratio");
	print_vector(stdout, data.t_ratio);
	puts("p value");
	print_vector(stdout, data.p_value);
	puts("std. error");
	print_vector(stdout, data.std_error);
	CLEAN_EXCEPTION;
    return 0;
}
