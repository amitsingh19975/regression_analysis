<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include "../include/exception.h"
#include "../include/string.h"

int main(int argv, char** argc){
	string str = csts("hello world");
	string temp;
	TRY{	
		temp = substr(&str, 1,3);
	}CATCH(runtime_error){
		printf("hell: %s\n",exception->what);
	}ETRY;
	print_str(&temp);
	return 0;
}
=======
#include "../lib/include/statistics.h"
#include "../lib/include/utility.h"
#include<stdlib.h>
#include<time.h>

int main(int argc, char const *argv[])
{
    srand(time(0));
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
    return 0;
}
>>>>>>> fe9239b81930f6abec3dd5655cd2805f8e24c0a2
