#ifndef PRINT_UTIL_H
#define PRINT_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>

#ifndef PRINTF_BUFFER_SIZE
	#define PRINTF_BUFFER_SIZE 100
#endif

/**@brief it is use to print error message
 *
 * @param fmt type of const char* for formated string
 * @param ... type of varadic args for passing args for fmt
 * @return size of the printed string
 *
 */
size_t eprint(const char* fmt, ... );

/**@brief it is use to print warning message
 *
 * @param fmt type of const char* for formated string
 * @param ... type of varadic args for passing args for fmt
 * @return size of the printed string
 *
 */
size_t wprint(const char* fmt, ... );

/**@brief it is use to print success message
 *
 * @param fmt type of const char* for formated string
 * @param ... type of varadic args for passing args for fmt
 * @return size of the printed string
 *
 */
size_t sprint(const char* fmt, ... );

/**@brief it is use to print exception
 *
 * @param fmt type of const char* for formated string
 * @param ... type of varadic args for passing args for fmt
 * @return size of the printed string
 *
 */
size_t exception_print( const char* excep_name, const char* fmt, ... );

#endif

