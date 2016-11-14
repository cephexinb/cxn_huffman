#pragma once
#include <stdio.h>
#include "Globals.h"
class BufferedReader{
private:
	unsigned char *buffer;
	FILE *stream;
	unsigned int pointer,bufferDataSize,bitPointer;
	unsigned char currentChar;
	void initialize(FILE *stream);
	void readData();
public:
	BufferedReader(FILE *stream);
	BufferedReader(const char *filename);
	~BufferedReader();

	unsigned char readChar();
	unsigned char readBit();
	char eof();
	FILE *getStream();
	void reset();
	void completeCurrentBit();

	void close();
};