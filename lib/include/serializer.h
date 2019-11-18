#ifndef SERAILIZER_H
#define SERAILIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_block.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include "exception.h"


typedef struct {
	size_t s1;
	size_t s2;
} sgeneral_header;


typedef struct {
	double* data;
} sbody;

int serialize_m( gsl_matrix* mat, const char* filename );
int serialize_v( gsl_vector* vec, const char* filename );
int deserialize_m( gsl_matrix* mat, const char* filename);
int deserialize_v( gsl_vector* vec, const char* filename);

#endif
