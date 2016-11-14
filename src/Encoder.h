#pragma once

#include <stdio.h>
#include <string.h>
#include "Globals.h"
#include "Header.h"

class Encoder{
private:
	BSTNode **analyzeFile(BufferedReader *br);
	Header *header;
	BufferedReader *br;
	unsigned int fileSize;

public:
	Encoder(const char *inputFilename);
	void encode(const char *outputFilename);
	~Encoder();
};