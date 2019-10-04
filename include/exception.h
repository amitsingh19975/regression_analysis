#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#define EXCEPTION_BUFFER_SIZE 100
#define TRY do{ __is_exception_handled__ = 1; switch( setjmp(__exception_buffer__) ) { case 0: while(1) {
#define CATCH( type ) break; case type:
#define FINALLY break; } default: {
#define ETRY break;} }} while(0); __is_exception_handled__ = 0

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
static __exception_type__ exception;
static int __is_exception_handled__ = 0;
void __exception_type_init__( int c, const char* err);
void __print_exception_type__();

void throw( int type, const char* mess );

#endif
