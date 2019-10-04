#include <stdio.h>
#include <stdlib.h>
#include "../include/exception.h"
#include "../include/string.h"

int main(int argv, char** argc){
	string str = csts("hello world");
	string temp;
	TRY{	
		temp = substr(&str, 1,3);
	}CATCH(runtime_error){
		printf("hell: %s\n",exception->what);
	}ETRY;
	print_str(&temp);
	return 0;
}
