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
	char csv_file[] = "/home/sphinx/Downloads/datasets/slr1/data1.csv";
	csv_frame *frame = parse_csv(csv_file);
	char mat_data_file[] = "/tmp/startmat.data";
	write_gsl_matrix(mat_data_file, frame, 0);
	// gsl_matrix *mat = matrix_file(mat_data_file);
	// print_matrix(stdout, mat);
	
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
	ols_data data =  reg_ols_linear_get_data(mat, coff, cov, chisq);
	puts("t-ratio");
	print_vector(stdout, data.t_ratio);
	puts("p value");
	print_vector(stdout, data.p_value);
	puts("std. error");
	print_vector(stdout, data.std_error);
	printf("F = %g\n", data.stats.f);
	printf("p-value-f = %g\n", data.stats.p_value_f);
	printf("R-sqrd = %g\n", data.stats.r_sqrd);
	printf("Ajusted R-sqrd = %g\n", data.stats.adj_r_sqrd);
	puts("\n\n\n\n\n\n\n\n");
	print_metrics( &data, 3 );
	/*
	gsl_vector *regressor = gsl_vector_alloc((mat->size2));
	for (size_t i = 0; i < mat->size2; i++)
	{
		gsl_vector_set(regressor, i, gsl_matrix_get(mat, 0, i));
	}
	gsl_vector_set(regressor, 0, 1);
	puts("X values from first row");
	print_vector(stdout, regressor);
	double y, y_err;
	reg_ols_linear_predict(regressor, coff, cov, &y, &y_err);
	printf("Predicted y = %g with error = %g\n", y, y_err);
	*/
	puts("\n\n\n\n\n\n\n\n");
	CLEAN_EXCEPTION;
    return 0;
}
