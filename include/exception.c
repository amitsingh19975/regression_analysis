#include "exception.h"

void throw_helper( int type ){
	longjmp( __exception_buffer__, type );
}

void throw( int type, const char* mess ){
	__exception_type_init__(type,mess);
	printf("%p\n",__is_exception_handled__);
	if( __is_exception_handled__ && *__is_exception_handled__){
		throw_helper(type);
	}else{
		__print_exception_type__();	
		exit(1);
	}
}

void __exception_type_init__( int c, const char* err ){
	if( exception == NULL ){
		exception = (__exception_type__*)calloc(1,sizeof(__exception_type__));
	}
	exception->type = c;
	strcpy( exception->what,err);
}

void __print_exception_type__(){
	switch( exception->type ){
		case 1: printf("excecption: runtime_error \n%s",exception->what); break;
		case 2: printf("excecption: out_of_bound \n%s",exception->what); break;
		case 3: printf("excecption: allocation_error \n%s",exception->what); break;
	};
}

void __init_exception_handled__(){
	if( __is_exception_handled__ == NULL )
		__is_exception_handled__ = (int*)calloc(1,sizeof(int));
}

void __clean_exception__(){
	free(__is_exception_handled__);
	free(exception);
}
