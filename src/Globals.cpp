#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include "Globals.h"


// print an error and exit
void error(const char *message){
	fprintf(stderr,"%s\n",message);
	exit(1);
//	throw new exception(message);
}