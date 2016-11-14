#pragma once

#include <stdio.h>
#include "Globals.h"

class BufferedWriter{
private:
	unsigned char *buffer;
	unsigned char bitBuffer;
	FILE *stream;
	unsigned int pointer,bufferDataSize,bitPointer,totalBytesWritten;
	void initialize(FILE *stream);
	void writeData();
public:
	BufferedWriter(FILE *stream);
	BufferedWriter(const char *filename);
	~BufferedWriter(void);

	void writeChar(unsigned char c);
	void writeBit(unsigned char bit);

	void completeCurrentBits(unsigned char toFillBit);

	FILE *getStream();
	unsigned int getTotalBytesWritten();

	void close();
} ;
