#include <stdio.h>
#include <string.h>
#include "Encoder.h"
#include "Decoder.h"


int main(int argc,char *argv[]){
//	printf("\n");
	if(argc < 4){
		printf("Usage: program [cd] InputFile OutputFile\n");
		return 1;
	}
	char *outFile = argv[3];
	char *inpFile = argv[2];
	char option = argv[1][0];
	if(option == 'e') option = 'c'; // e = encode = compress !
	if(option != 'c' && option != 'd'){
		printf("Usage: program [cd] InputFile OutputFile\n");
		return 1;
	}

	if(option == 'c'){
		Encoder *enc = new Encoder(inpFile);
		enc->encode(outFile);
	} else {
		Decoder *dec = new Decoder(inpFile);
		dec->decode(outFile);
	}


	return 0;
}