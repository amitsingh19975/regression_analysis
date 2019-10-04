#include "exception.h"

void throw( int type, const char* mess ){
	__exception_type_init__(type,mess);
	if( !__is_exception_handled__ ){
		longjmp( __exception_buffer__, type);
	}else{
		__print_exception_type__();	
		exit(1);
	}
}

void __exception_type_init__( int c, const char* err ){
	exception.type = c;
	strcpy( exception.what, err);
}

void __print_exception_type__(){
	switch( exception.type ){
		case 1: printf("excecption: runtime_error \n%s",exception.what); break;
		case 2: printf("excecption: out_of_bound \n%s",exception.what); break;
		case 3: printf("excecption: allocation_error \n%s",exception.what); break;
	};
}
