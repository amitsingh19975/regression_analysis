#include "include/print_util.h"

size_t eprint( const char* fmt, ... ){
	va_list args;
	va_start(args,fmt);
	char mess[PRINTF_BUFFER_SIZE] = {0};
	sprintf(mess,"\x1b[0;31mError: %s\x1b[0m",fmt);
	size_t size = vprintf(mess,args);
	va_end(args);
	return size;
}
size_t wprint( const char* fmt, ... ){
	va_list args;
	va_start(args,fmt);
	char mess[PRINTF_BUFFER_SIZE] = {0};
	sprintf(mess,"\x1b[0;33mWarning: %s\x1b[0m",fmt);
	size_t size = vprintf(mess,args);
	va_end(args);
	return size;
}
size_t sprint( const char* fmt, ... ){
	va_list args;
	va_start(args,fmt);
	char mess[PRINTF_BUFFER_SIZE] = {0};
	sprintf(mess,"\x1b[0;32mSuccess: %s\x1b[0m",fmt);
	size_t size = vprintf(mess,args);
	va_end(args);
	return size;
}

size_t exception_print( const char* excep_name, const char* fmt, ... ){
	va_list args;
	va_start(args,fmt);
	char mess[PRINTF_BUFFER_SIZE] = {0};
	sprintf(mess,"\x1b[0;31mException: %s\x1b[0m\n%s",excep_name,fmt);
	size_t size = vprintf(mess,args);
	va_end(args);
	return size;
}


void print_matrix(FILE* file,const gsl_matrix * mat) {
    for (size_t i = 0; i < mat->size1; i++)
    {
        for (size_t j = 0; j < mat->size2; j++)
        {
            fprintf(file, "%g\t", gsl_matrix_get(mat, i, j));
        }
        fprintf(file, "\n");
    }
}

void print_vector(FILE* file,const gsl_vector * vec) {
    size_t i;
    for (i = 0; i < (vec -> size) - 1; i++)
    {
        fprintf(file, "%g, ", gsl_vector_get(vec, i));
    }
    fprintf(file, "%g\n", gsl_vector_get(vec, i));
}
