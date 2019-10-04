#include "string.h"
#include "exception.c"

int __new_str__(string* str, index_t cap){
	str->capacity = cap;
	str->size = 0;
	str->data = (char*)calloc(str->capacity,sizeof(char));

	if( str->data == null ){
		return STR_ALLOC_ERR;
	}else {
		return 0;
	}
}

int str_init( string* str ){
	return __new_str__(str,24);
}

void delete_str( string* str ){
	str->capacity = 0;
	str->size = 0;
	free( str->data );
	str->data = null;
}

int appendcs( string* dest, const char* src ){
	index_t src_size = strlen(src);
	index_t dest_size = dest->size;
	index_t new_size = dest->size + src_size;
	
	index_t cap = dest->capacity;
	if( cap <= new_size ){
		while( cap <= new_size ) cap *= 2;
	
		dest->data = (char*)realloc( dest->data, cap );

		if( dest->data == null ){
			return STR_ALLOC_ERR;
		}
		
		dest->capacity = cap;
		dest->size = new_size;
	}

	for( index_t i = 0; i < src_size; ++i ){
		dest->data[ dest_size + i ] = src[i];
	}
	
	dest->data[ new_size ] = '\0';
	return 0;

}

int appends( string* dest, string* src ){
	return appendcs( dest, src->data );
}

int appendc( string* dest, char c ){
	char temp[2] = {c,0};
	return appendcs( dest,temp );
}

int strcpycs( string* dest, const char* src ){
	index_t src_size = strlen(src);

	index_t cap = 24;
	if( cap <= src_size ){
		while( cap <= src_size ) cap *= 2;
	
		dest->data = (char*)realloc( dest->data, cap );
	
		if( dest->data == null ){
			return STR_ALLOC_ERR;
		}
	}
	memcpy( dest->data, src, src_size );

	dest->capacity = cap;
	dest->size = src_size;

	return 0;
}

int strcpys( string* dest, string* src ){
	return strcpycs( dest, src->data );
}

string substr( string* str, index_t i, index_t j ){
	index_t s = 0, e = 0;
	index_t str_size = str->size;
	printf("%ld %ld\n",i,j);
	if( i > j ){
		i ^= j;
		j = i ^ j;
		i = i ^ j;
	}

	if( i >= 0 && j >= 0 ){
		s = i;
		e = j;
	}else if( i < 0 && j < 0 ){
		i = -i;
		j = -j;
		s = str_size - ( i % str_size );
		e = str_size - ( j % str_size );
		return substr( str, s, e );
	}else if ( i < 0 && j >= 0 ){
		i = -i;
		s = str_size - ( i % str_size );
		e = j;
		return substr( str, s, e );
	}

	string temp;
	index_t cap = 24;
	
	while( cap <= e - s ) cap *= 2;
	__new_str__( &temp, cap );
	
	temp.size = e - s;
	temp.capacity = cap;
	for( ; s < e; ++s ){
		appendc(&temp,at(str,s));
	}
	return temp;
}

index_t findcs( string* str, const char* pat ){
	char* f = strstr( str->data, pat);
	if( f == null ){
		return STR_NPOS;
	}else{
		return (f - str->data);
	}
}

index_t finds( string* str, string* pat ){
	return findcs(str,pat->data);
}

char* c_str( string* str ){
	return str->data;
}

string csts( const char* str ){
	string temp;
	str_init( &temp );
	appendcs( &temp, str );
	return temp;
}

char at( string* str, index_t i ){
	index_t sz = str->size;
	if( sz == 0 ){
		throw( runtime_error,"at : size is zero " );
	}
	if( i < 0 ){
		i = -i;
		i = sz - ( i & sz);
	}else if( i >= sz){
		i = i % sz;
	}
	return str->data[i];
}

char* p_at( string* str, index_t i ){
	index_t sz = str->size;
	if( i < 0 ){
		i = -i;
		i = sz - ( i & sz);
	}else if( i >= sz ){
		i = i % sz;
	}
	return (str->data + i);
}

void print_str( const string* str ){
	printf("%s\n",str->data);
}
