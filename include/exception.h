#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#define EXCEPTION_BUFFER_SIZE 100
#define __INIT_EXCEPTION_HANDLE__ 	if( __is_exception_handled__ == NULL ){ \
						__is_exception_handled__ = (int*)calloc(1,sizeof(int));}
#define TRY do{ __init_exception_handled__(); *__is_exception_handled__ = 1; switch( setjmp(__exception_buffer__) ) { case 0: while(1) {
#define CATCH( type ) break; case type:
#define FINALLY break; } default: {
#define ETRY break;} }} while(0); *__is_exception_handled__ = 0; __clean_exception__()

enum{
	runtime_error = 1,
	out_of_bound,
	allocation_error
};

typedef struct{
	int type;
	char what[EXCEPTION_BUFFER_SIZE];
} __exception_type__;

jmp_buf __exception_buffer__;
static __exception_type__* exception = NULL;
static int* __is_exception_handled__ = NULL;

void __exception_type_init__( int c, const char* err);
void __init_exception_handled__();
void __print_exception_type__();
void __clean_exception__();

void throw( int type, const char* mess );

#endif
