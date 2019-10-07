#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include "print_util.h"

#ifndef EXCEPTION_BUFFER_SIZE
	#define EXCEPTION_BUFFER_SIZE 100
#endif

#define INIT_EXCEPTION __init_exception__()
#define CLEAN_EXCEPTION __clean_exception__()
#define HANDLE_EXCEPTION (__is_exception_handled__ = &__exception_on__)
#define NOT_HANDLE_EXCEPTION (__is_exception_handled__ = &__exception_off__)

#define TRY 	\
		HANDLE_EXCEPTION;\
		do{\
		switch( setjmp(__exception_buffer__) ) {\
		case 0: while(1) {
#define CATCH( type ) break; case type:
#define FINALLY break; } default: {
#define ETRY break;} }} while(0); NOT_HANDLE_EXCEPTION

/**@brief enumerate for different types of exception*/
enum{
	runtime_error = 1,
	out_of_bound,
	allocation_error
};

/**@brief struct for storing type of exception and and message with it*/
typedef struct{
	int type;
	char what[EXCEPTION_BUFFER_SIZE];
} __exception_type__;

/**brief jump buffer for longjmp*/
jmp_buf __exception_buffer__;

/**brief exception object in register for global variable*/
register __exception_type__* exception asm("r13");

/**brief it is use to check it exception is handled or not*/
register int *__is_exception_handled__ asm ("r12");

/**brief turns off exception handling*/
static int __exception_off__ = 0;

/**brief turns on exception handling*/
static int __exception_on__ = 1;

/**brief it is use to initialize exception object
 *
 * @param c type of int for error code
 * @param err type of const char* for exception message;
 *
 */
void __exception_type_init__( int c, const char* err);

/**brief it is use to initialize exception*/
void __init_exception__();

/**brief it is use to print exception in buffer*/
void __print_exception_type__();

/**brief it is use to clean exception*/
void __clean_exception__();

/**@brief it is use to throw exception
 *
 * @param type type of int for exception type
 * @param mess type const char* for message
 *
 */
void throw( int type, const char* mess );

#endif
