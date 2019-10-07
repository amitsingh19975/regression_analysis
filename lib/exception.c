#include "include/exception.h"

void throw_helper( int type ){
	longjmp( __exception_buffer__, type );
}

void throw( int type, const char* mess ){
	__exception_type_init__(type,mess);
	if( *__is_exception_handled__ ){
		throw_helper(type);
	}else{
		__print_exception_type__();	
		exit(1);
	}
}

void __exception_type_init__( int c, const char* err ){
	exception->type = c;
	strncpy( exception->what, err, EXCEPTION_BUFFER_SIZE - 1);
}

void __print_exception_type__(){
	switch( exception->type ){
		case runtime_error: exception_print("runtime_error",exception->what); break;
		case out_of_bound: exception_print("out_of_bound",exception->what); break;
		case allocation_error: exception_print("allocation_error",exception->what); break;
	};
}

void __init_exception__(){
	__is_exception_handled__ = &__exception_off__;	
	exception = (__exception_type__*)calloc(1,sizeof(__exception_type__));
	exception->what[0] = 0;
}

void __clean_exception__(){
	__is_exception_handled__ = &__exception_on__;
	
	if( exception ){
		free(exception);
		exception = NULL;
	}

}

