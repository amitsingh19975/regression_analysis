#include <stdio.h>
#include <stdlib.h>
#include "../lib/include/exception.h"
#include "../lib/include/string.h"
#include "../lib/include/statistics.h"
#include "../lib/include/utility.h"
#include "../lib/include/csv_parser.h"
#include<time.h>


int main(int argc, char const *argv[])
{	
	INIT_EXCEPTION;
	const char* f = "/home/amit/Desktop/test.csv";
	parse_csv(f);

/*  srand(time(0));
    size_t n = 3;
    gsl_matrix *mat = gsl_matrix_alloc(n, n);
    for (size_t i = 0; i < mat -> size1; i++)
    {
        for (size_t j = 0; j < mat -> size2; j++)
        {
            gsl_matrix_set(mat, i, j, rand()%100 + 1);
        }
    }

    printf("Matrix A: \n");
    print_matrix(stdout, mat);
    gsl_matrix_free(mat);
    */
	CLEAN_EXCEPTION;
    return 0;
}
