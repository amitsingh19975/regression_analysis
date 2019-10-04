#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "exception.h"

#define null (void*)0

typedef ptrdiff_t index_t;

enum STRING_ERROR{
	STR_NPOS = -1,
	STR_ALLOC_ERR = 1,
	STR_NOT_NULL,
};

/**@brief string is wrapper around C string which provides dynamic
 * resizing of string
 */

typedef struct{
	char* data;
	index_t size;
	index_t capacity;
} string;


/**@brief str_init is use to initialize string
 *
 * @param str type of string
 * @return STRING_ERROR code or 0 for no error
 *
 */
int str_init( string* str );

/**@brief __new_str__ creates new string with specified capacity
 *
 * @param str type of string
 * @return STRING_ERROR code or 0 for no error
 *
 */
int __new_str__( string* str, index_t cap);

/**@brief duplicates the string
 * 
 * @param str of type string
 * @return string otherwise null
 *
 */
string* dups( string* str );

/**@brief appends is use to append string to the string
 * 
 * @param dest type of string
 * @param src type of string
 * @return STRING_ERROR code or 0 for no error
 *
 */
int appends( string* dest, string* src );

/**@brief appendcs is use to append string to the string
 * 
 * @param dest type of string
 * @param src type of string
 * @return true if able to append or false for error
 * @return STRING_ERROR code or 0 for no error
 *
 */
int appendcs( string* dest, const char* src);

/**@brief appendc is use to append string to the string
 * 
 * @param dest type of string
 * @param src type of const char*
 * @return true if able to append or false for error
 * @return STRING_ERROR code or 0 for no error
 *
 */
int appendc( string* dest, char c);

/**@brief strcpys is use to copy string to the string
 * 
 * @param dest type of string
 * @param src type of string
 * @return STRING_ERROR code or 0 for no error
 *
 */
int strcpys( string* dest, string* src);

/**@brief strcpycs is use to copy string to the string
 * 
 * @param dest type of string
 * @param src type of const char
 * @return STRING_ERROR code or 0 for no error
 *
 */
int strcpycs( string* dest, const char* src);

/**@brief substr is use to get subtring from string
 * 
 * @param str type of string
 * @param i type of index_t
 * @param j type of index_t
 * @return substring between i and j
 *
 */
string substr( string* str, index_t i, index_t j);

/**@brief findcs is use to find subtring if exist
 * 
 * @param s1 type of string
 * @param s2 type of const char*
 * @return position of subtring otherwise STR_NPOS
 *
 */
index_t findcs( string* s1, const char* s2);

/**@brief finds is use to find subtring if exist
 * 
 * @param s1 type of string
 * @param s2 type of string
 * @return position of subtring otherwise STR_NPOS
 *
 */
index_t finds( string* s1, string* s2);

/**@brief c_str is use to convert string to C string
 * 
 * @param str type of string
 * @return char* if string is not NULL otherwise NULL
 *
 */
char* c_str( string* str );

/**@brief csts is use to convert C string to string
 * 
 * @param str type of const char*
 * @return string
 *
 */
string csts( const char* str );


/**@brief delete_str is use to deletes the string properly
 * 
 * @param str type of string
 *
 */
void delete_str( string* str);

/**@brief at gets the char at a given position
 *
 * @param str type of string
 * @param i type of index_t for index
 * @return char at index i
 *
 */
char at(string* str, index_t i);


/**@brief p_at gets the char* at a given position
 *
 * @param str type of string
 * @param i type of index_t for index
 * @return char* at index i
 *
 */
char* p_at(string* str, index_t i);

/**@brief prints the string 
 *
 * @param str type of string
 *
 */
void print_str( const string* str );

#endif
