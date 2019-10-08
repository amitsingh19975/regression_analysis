#include <stdio.h>
#include <stdlib.h>
#include "../lib/include/exception.h"
#include "../lib/include/string.h"
#include "../lib/include/statistics.h"
#include "../lib/include/utility.h"
#include "../lib/include/csv_parser.h"
#include<time.h>


int main(int argc, char const *argv[])
{	
	INIT_EXCEPTION;
	const char* f = "/home/amit/Desktop/cancer_reg.csv";
	csv_frame* t = parse_csv(f);
	
	write_gsl_matrix(t,3,0,1,2);
	
	CLEAN_EXCEPTION;
    return 0;
}
