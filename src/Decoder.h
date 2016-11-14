#pragma once

#include <stdio.h>
#include <string.h>
#include "Globals.h"
#include "BufferedReader.h"
#include "BufferedWriter.h"
#include "Header.h"

class Decoder{
	BufferedReader *br;
	Header *header;

public:
	Decoder(const char *inputFilename);
	~Decoder(void);

	void decode(const char *outputFilename);
};
