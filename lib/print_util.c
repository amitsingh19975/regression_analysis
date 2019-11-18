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

void push_c( string* str, char c, int sz ){
	for( ; sz >= 0; --sz ) appendc( str, c );
}

void push_str( string* str, const char* s, int sp ){
	appendcs( str, s);
        push_c( str, ' ', sp - strlen(s));
}

string dstring(double num){
	char ret[20] = "%.";
	char ds[20] = {0};
	char prec[10] = {0};
	int temp = PREC;
	int idx = 0;
	while( temp != 0 ){
		int d = temp % 10;
		temp /= 10;
		prec[idx++] = d + '0';
	}
	strcat(ret,prec);
	strcat( ret,"f");
	sprintf(ds,ret,num);
	return csts(ds);
}

void print_metrics( const ols_data* s, int sp ){
	string head = csts(""), body = csts("");
	int max_s = 11;
	int width = ( max_s + sp ) * 5;
	const char arr[4][12] = {
		"Coefficient",
		"std. error",
		"t-ratio",
		"p-value"
	};
	const gsl_vector* colVec[] = {
		s->coefficient,
		s->std_error,
		s->t_ratio,
		s->p_value
	};
	size_t col = 4;

	const char heading[] = "Metrics";
	int heading_width = width - sizeof(heading);
	int mid = heading_width / 2;
	push_c( &head, '-', mid );
	appendcs(&head,heading);
	push_c( &head, '-', mid );
	appendc(&head,'\n');
	appendc(&head,'\n');
	
	push_c( &head, ' ', max_s + sp );
	push_str( &head, arr[0], sp+max_s);	
	push_str( &head, arr[1], sp+max_s);	
	push_str( &head, arr[2], sp+max_s);	
	push_str( &head, arr[3], sp+max_s);	
	appendc(&head,'\n');
	push_c( &head,'-',width);

	push_str( &body, "const", sp+max_s);
	for( int i = 0; i < col; i++ ){
		const gsl_vector* el = colVec[i];
		if( el == NULL ) return;
		double t = gsl_vector_get( el, 0 );
		string d = dstring(t);
		push_str( &body, c_str(&d), sp + max_s );
		delete_str(&d);
	}

	appendc( &body, '\n' );

	for( int i = 1; i < s->coefficient->size; i++ ){
		char temp[10] = {0};
		sprintf(temp,"C%d",i);
		push_str( &body, temp, sp+max_s );
		for( int j = 0; j < col; j++ ){
			const gsl_vector* el = colVec[j];
			if( el == NULL ) return;
			double t = gsl_vector_get( el, i );
			string d = dstring(t);
			push_str( &body, c_str(&d), sp + max_s );
			delete_str(&d);
		}
		appendc(&body,'\n');
	}
	printf("%s\n",c_str(&head));
	printf("%s\n\n\n",c_str(&body));
	
	delete_str(&head);
	delete_str(&body);
	
	ols_stats_data sdata = s->stats;
	string stats[] = {
		dstring(sdata.mean_dependent_var),
		dstring(sdata.sd_dependent_var),
		dstring(sdata.se_regression),
		dstring(sdata.r_sqrd),
		dstring(sdata.adj_r_sqrd),
		dstring(sdata.f),
		dstring(sdata.p_value_f),
	};
	printf("Mean Dependent Var: %s	S.D. Dependent Var: %s\n", c_str(&stats[0]), c_str(&stats[1]));
	printf("S.E. Regression	  : %s	R-squred: 	    %s\n", c_str(&stats[2]), c_str(&stats[3]));
	printf("Adjusted R-squared: %s	F: 		    %s\n", c_str(&stats[4]), c_str(&stats[5]));
	printf("P-value( F ): 	    %s\n", c_str(&stats[6]));
	
	for( int i = 0; i < 7; i++) delete_str(&stats[i]);
}
