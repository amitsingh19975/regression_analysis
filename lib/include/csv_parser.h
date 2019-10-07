#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "exception.h"
#include <ctype.h>

/**@breif it is use to store rows in csv frame*/
typedef struct{
	string* data;
	index_t capacity;
	index_t size;
} csv_row;

/**@breif it is use to store header in csv frame*/
typedef csv_row csv_header;

/**@breif it is use to store whole csv which contains header and body*/
typedef struct{
	csv_header* header;
	csv_row* body;
	index_t size;
	index_t capacity;
} csv_frame;

/**@breif it is use to allocate memory for csv_row
 *
 * @param r type of csv_row* which is not null
 * @param cap type of index_t for specifying capacity
 *
 */
void __new_crow__( csv_row* r, index_t cap );

/**@breif it is use to allocate memory for csv_frame
 *
 * @param f type of csv_frame* which is not null
 * @param cap type of index_t for specifying capacity
 *
 */
void __new_cframe__( csv_frame* f, index_t cap );

/**@breif it is use to initialize csv_row
 *
 * @param r type of csv_row* which is not null
 *
 */
void init_crow( csv_row* r );

/**@breif it is use to initialize csv_frame
 *
 * @param f type of csv_frame* which is not null
 *
 */
void init_cframe( csv_frame* f );

/**@breif it is use to insert string into csv_row
 *
 * @param r type of csv_row* which is not null
 * @param s pointer to string
 *
 */
void insert_crow( csv_row* r, string* s);

/**@breif it is use to insert csv_row into csv_frame
 *
 * @param f pointer to csv_frame
 * @param r pointer to csv_row
 *
 */
void insert_cbody( csv_frame* f, csv_row* r);

/**@breif it is use to get pointer to element in csv_row at 
 * given pos
 *
 * @param r pointer to csv_row
 * @param k index of the element
 * @return string pointer stored at given index;
 *
 */
string* p_at_crow( csv_row* r, index_t k);

/**@breif it is use to get pointer to element in csv_frame at 
 * given pos
 *
 * @param f pointer to csv_frame
 * @param k index of the element
 * @return csv_row pointer stored at given index;
 *
 */
csv_row* p_at_cframe( csv_frame* f, index_t k );

/**@breif it is use to frees the memory allocated to csv_row 
 *
 * @param r pointer to csv_row
 *
 */
void delete_crow( csv_row* r );

/**@breif it is use to frees the memory allocated to csv_frame 
 *
 * @param f pointer to csv_frame
 *
 */
void delete_cframe( csv_frame* f );

/**@breif it is use to prints the csv_frame 
 *
 * @param f pointer to csv_frame
 *
 */
void print_csv( csv_frame* f );

/**@breif it is use to parse CSV
 *
 * @param filename const pointer to char
 * @return pointer to the csv_frame which maybe null
 *
 */
csv_frame* parse_csv( const char* filename );

/**@breif it is use to parse single row of CSV
 *
 * @param fp pointer to FILE
 * @param sep type const char which is used to define 
 * type of separator
 * @param dec type const char which is used to define
 * type of decimal separator
 * @return pointer to csv_row which maybe null
 *
 */
csv_row* parse_row( FILE* fp, const char sep, const char dec);

/**@breif it is a generalized CSV parser which can be converted
 * to DSV easily just by changine sep and dec
 *
 * @param filename const pointer to string containing filename
 * @param separator type const char which is used to define 
 * type of separator
 * @param decimal type const char which is used to define
 * type of decimal separator
 * @return pointer to csv_frame which maybe null
 *
 */
csv_frame* general_csv_parser( const char* filename, const char separator, const char decimal);

#endif
