#include "include/serializer.h"
/*
int serialize_m( gsl_matrix* mat, const char* filename ){
	if( mat == NULL && mat->data == NULL){
                throw(runtime_error,"matrix is null");
        }
        FILE* f;
        f = fopen( filename, "wb" );
	
	if( f == NULL ){
		throw( runtime_error, "File not found" );
	}

        sgeneral_header gh = {.s1 = mat->size1, .s2 = mat->size2};

	sbody b = { .data = mat->data };
	
	fwrite( (char*)&gh, sizeof( gh ), 1, f );
	fwrite( (char*)b.data, sizeof(size_t) * gh.s1 * gh.s2, 1, f );
	fclose(f);
	return 0;
}

int serialize_v( gsl_vector* vec, const char* filename ){
        if( vec == NULL && vec->data == NULL){
                throw(runtime_error,"matrix is null");
        }
        FILE* f;
        f = fopen( filename, "wb" );
	
	if( f == NULL ){
		throw( runtime_error, "File not found" );
	}

        sgeneral_header gh = {.s1 = vec->size, .s2 = vec->stride };

        sbody b = { .data = vec->data};

        fwrite( (char*)&gh, sizeof( gh ), 1, f );
        fwrite( (char*)b.data, sizeof(size_t) * gh.s1 * gh.s2, 1, f );
        fclose(f);
	return 0;
}

int deserialize_m( gsl_matrix* mat, const char* filename ){
        if( mat == NULL && mat->data == NULL){
                throw(runtime_error,"matrix is null");
        }
        FILE* f;
        f = fopen( filename, "rb" );
	
	if( f == NULL ){
		throw( runtime_error, "File not found" );
	}

        sgeneral_header gh;

        sbody b = { .data = mat->data };

        fread( (char*)&gh, sizeof( gh ), 1, f );
	mat = gsl_matrix_alloc( gh.s1, gh.s2 );
        fread( (char*)b.data, sizeof() * gh.s1 * gh.s2, 1, f );
        fclose(f);
	return 0;
}

int deserialize_v( gsl_matrix* vec, const char* filename ){
        if( vec == NULL && vec->data == NULL){
                throw(runtime_error,"matrix is null");
        }
        FILE* f;
        f = fopen( filename, "rb" );

        if( f == NULL ){
                throw( runtime_error, "File not found" );
        }

        sgeneral_header gh;

        sbody b = { .data = vec->data };

        fread( (char*)&gh, sizeof( gh ), 1, f );
        vec = gsl_vector_alloc( gh.s1 );
        fread( (char*)b.data, sizeof(size_t) * gh.s1, 1, f );
        fclose(f);
        return 0;
}
*/
