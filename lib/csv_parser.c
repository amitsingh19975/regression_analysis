#include "include/csv_parser.h"

void __new_crow__( csv_row* r, index_t cap ){
	if( r == null ){
		throw( runtime_error, "init_crow: csv_row is null");
	}
	r->capacity = cap;
	r->size = 0;

	r->data = (string*)calloc(r->capacity, sizeof(string));
	if( r->data == null ){
		throw( allocation_error,"init_crow: unable to allocate");
	}
}

void __new_cframe__( csv_frame* f, index_t cap ){
	if( f == null ){
		throw( runtime_error, "init_cframe: csv_frame is null");
	}
	f->capacity = cap;
	f->size = 0;
	
	f->body = (csv_row*)calloc(f->capacity,sizeof(csv_row));
	
	if( f->body == null ){
		throw( allocation_error,"init_cframe: unable to allocate");
	}
}

void init_crow( csv_row* r ){
	__new_crow__( r, 10 );
}

void init_cframe( csv_frame* f ){
	__new_cframe__(f,10);
}

void insert_crow( csv_row* r, string* s){
	if( r == null || s == null ){
		throw( runtime_error, "insert_crow: null pointer exception");
	}

	index_t cap = r->capacity;
	if( cap <= r->size ){
		while( cap <= r->size ) cap *= 2;
		r->data = (string*)realloc( r->data, cap * sizeof(string) );
		r->capacity = cap;
	}
	index_t l = (r->size)++;
	__new_str__(&(r->data[l]),s->size);

	memmove( r->data[l].data, s->data,s->size );
	r->data[l].size = s->size;
}

void insert_cbody( csv_frame* f, csv_row* r ){
	if( r == null || f == null ){
		throw( runtime_error, "insert_cbody: null pointer exception");
	}

	index_t cap = f->capacity;
	if( cap <= f->size ){
		while( cap <= f->size ) cap *= 2;
		f->body = (csv_row*)realloc( f->body, sizeof(csv_row) * cap );
		if( f->body == null ){
			throw(allocation_error,"insert_cbody: unable to allocate memory");
		}
		f->capacity = cap;
	}
	index_t l = (f->size);
	f->size = f->size + 1;	
	
	f->body[l].data = r->data;
	f->body[l].size = r->size;
	f->body[l].capacity = r->capacity;
	r->data = null;
	r->size = 0;
	r->capacity = 0;
	free(r);
}

string* p_at_crow( csv_row* r, index_t k ){
	
	if( r->size <= k || k < 0 ){
		throw( out_of_bound, "p_at_crow: out of bound access of data");
	}
	return &(r->data[k]);
}
csv_row* p_at_cframe( csv_frame* r, index_t k ){
	
	if( r->size <= k || k < 0 ){
		throw( out_of_bound, "p_at_cframe: out of bound access of data");
	}
	return &(r->body[k]);
}

void delete_crow( csv_row* r ){
	if( r == null ) return;
	for(index_t i = 0; i < r->capacity; i++) delete_str( &(r->data[i]) );
	free(r->data);
}
void delete_cframe( csv_frame* f ){
	if( f == null ) return;
	for(index_t i = 0; i < f->capacity; i++) delete_crow( &(f->body[i]) );
	delete_crow((f->header));
	free( f->body );
}

void print_csv( csv_frame* f ){
	if( f == null ) {
		throw( runtime_error, "print_csv: csv_frame is null");
	}

	index_t rows = f->size;
	
	if( f->header == null ) {
		throw( runtime_error, "print_csv: csv_frame::header is null");
	}

	index_t cols = (f->header)->size;

	const int sp = 3;
	
	for( index_t i = 0; i < cols; i++){
		if( i > 0 ){
			for( int j = 0; j < sp; j++ ) printf(" ");
		}
		print_str( &((f->header)->data[i]) );
	}

	puts("");

	for( index_t i = 0; i < rows; i++){
		const csv_row* r = &(f->body[i]); 
		for( index_t j = 0; j < cols; j++){
			if( j > 0 ){
				for( int k = 0; k < sp; k++) printf(" ");
			}
			printf( "%s",r->data[j].data );
		}
		puts("");
	}
}

char fpeek( FILE* fp ){
	
	if( fp == null ){
		throw( runtime_error, "parse_row: file pointer is null");
	}
	char c = fgetc( fp );
	ungetc(c,fp);
	return 'c';
}

int is_str( const char c, const char dec){
	return ( isalnum(c) || c == dec );
}

csv_row* parse_row( FILE* fp, const char sep, const char dec ){
	if( fp == null ){
		throw( runtime_error, "parse_row: file pointer is null");
	}
	if( feof(fp) ) {
		return null;
	}
	
	csv_row* temp = (csv_row*)malloc(sizeof(csv_row));
	init_crow(temp);
	
	string temp_str;
	init_str(&temp_str);
	char c;
	while( (c = fgetc(fp)) != EOF ){
		if( fpeek(fp) == ' ' ){
			while( (c = fgetc(fp) == ' '));
		}	
		if( is_str(c,dec) ){
			appendc(&temp_str,c);		
		}else if( c == '"' ){
			int count = 1;
			while( (c = fgetc(fp)) != EOF){
				if( c == '"' ) ++count;
				
				if( (count & 1) == 0 ){
					if( fpeek(fp) == ' ' ) {
						while( (c = fgetc(fp)) == ' ' );
					}
					if( c == sep ){
						break;	
					}
				}
				if( (count & 1) == 1 && ( is_str(c,dec) || c == ' ' || c == '\n' || c == '"' ) ){
					appendc(&temp_str,c);
				}
			}
			insert_crow(temp,&temp_str);
			clear_str(&temp_str);

		}else if( c == '\n' ) {
			insert_crow(temp,&temp_str);
			delete_str(&temp_str);
			break;
		}else if( c == sep ){
			insert_crow(temp,&temp_str);
			clear_str(&temp_str);
		}
	}
	return temp;
}

csv_frame* general_csv_parser( const char* filename, char separator, char decimal ){
	FILE* fp = null;
	fp = fopen( filename, "r");
	if( fp == null ){
		throw( runtime_error, "parse_csv: file not found");
	}
	
	csv_frame* f = (csv_frame*)malloc(sizeof(csv_frame));
	
	if( f == null ){
		throw(allocation_error,"general_csv_parser: unable to allocate memory");
	}

	init_cframe(f);
	f->header = parse_row( fp, separator, decimal );
	if( f->header == null ) {
		delete_cframe(f);
		free(f);
		return null;
	}
	while( !feof(fp) ){ 
		insert_cbody( f, parse_row(fp, separator, decimal) ) ;
	}
	fclose(fp);
	return f;
} 

csv_frame* parse_csv( const char* filename ){
	return general_csv_parser( filename, ',', '.' );
}

int comp_for_index_t( const void* a, const void* b ){
	return *(index_t*)a - *(index_t*)b;
}

void write_gsl_matrix( csv_frame* f, index_t size, ... ){
	if( f == null ){
		throw( runtime_error, "write_gsl_matrix: csv_frame parameter is null");
	}
	if( f->header == null || f->body == null ){
		throw( runtime_error, "write_gsl_matrix: header or body of csv_frame is null");
	}
        if( size < 0 ){
                throw(runtime_error,"write_gsl_matrix: size cannot be negative value");
        }

        va_list args;
        va_start(args,size);

        index_t *idxs = null;
	index_t rows = f->size;
	index_t cols = f->header->size;

        if( size > 0 ){
                idxs = (index_t*)malloc( size * sizeof(index_t));
                if( idxs == null ){
                        throw( allocation_error, "write_gsl_matrix: unable to allocate memory");
                }

        }

        for(index_t i = 0; i < size; i++){
                idxs[i] = va_arg(args,index_t);
		if( idxs[i] >= cols ){
			free(idxs);
			throw( out_of_bound, "write_gsl_matrix: indics in variadic arguments are out of bound");
		}
        }

	if( idxs != null ){
		qsort((void*)idxs, size, sizeof(index_t),comp_for_index_t);
	}
	
	FILE* fp;
	fp = fopen( "/tmp/gsl_matrix.data", "w" );
	
	index_t obs = f->size;	
	
	size = ( size ? size : cols );
	for(index_t i = 0; i < rows; ++i){
                for( index_t j = 0; j < size; ++j){
                        index_t idx = ( idxs == null ? j : idxs[j] );
			
			if( empty( &(f->body[i].data[idx]) ) ){
				--obs;
				break;
                        }
                }
        }
	fprintf(fp,"%ld\n%ld\n",size,obs);

	
	string temp;
	init_str(&temp);
	
	for(index_t i = 0; i < rows; ++i){
		int flag = 0;
		for( index_t j = 0; j < size; ++j){
                        index_t idx = ( idxs == null ? j : idxs[j] );
			if( empty( &(f->body[i].data[idx]) ) ){
				flag = 1;
				break;
			}
			appends(&temp, &(f->body[i].data[idx]) );
			if( j != cols - 1 ){
				appendc(&temp,' ');
			}
		}
		if( !flag ){
			fprintf(fp,"%s\n",temp.data);
		}
		clear_str(&temp);	
	}

	fclose(fp);	
        va_end(args);
}

