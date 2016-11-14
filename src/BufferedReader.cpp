#include "BufferedReader.h"

/*
	BufferedReader:
		Bufferes a file data for input.
*/

// Use a file stream for input
BufferedReader::BufferedReader(FILE *stream){
	initialize(stream);
}

// Open a file for input
BufferedReader::BufferedReader(const char *filename){
	initialize(fopen(filename,"rb"));
}

BufferedReader::~BufferedReader(){
	if(this->stream	!= NULL)
		fclose(this->stream);
	if(this->buffer != NULL)
		delete [] this->buffer;
}

// Initialize variables
void BufferedReader::initialize(FILE *stream){
	this->pointer = 0; // Pointer in buffer , when pointer reaches buffer size , the buffer is empty !
	this->bufferDataSize = 0; // size of characters in the buffer
	this->bitPointer = 8; // bit pointer , used for reading file bit by bit

	this->buffer = new unsigned char[Globals::BUFFERED_READER_BUFFER_SIZE];
	if(stream == NULL)
		error("BufferedReader can't open input file !");
	this->stream = stream;
}

// Read data from file,this will be called when the buffer is empty
void BufferedReader::readData(){
	this->bufferDataSize = (int)fread(buffer,1,Globals::BUFFERED_READER_BUFFER_SIZE,this->stream);
	this->pointer = 0; // Reset buffer pointer to full
}

// End of file ?
char BufferedReader::eof(){
	// if buffer is empty try to read something from file
	if(this->pointer == this->bufferDataSize)
		readData();
	// if buffer is still empty it means that we have reached end of file
	return this->bufferDataSize == 0 && this->bitPointer >= 8;
}
unsigned char BufferedReader::readChar(){
	if(eof())
		error("End of file reached in buffered reader.");
	return this->buffer[this->pointer++];
}
unsigned char BufferedReader::readBit(){
	if(bitPointer >= 8){
		currentChar = readChar();
		bitPointer = 0;
	}
	return (this->currentChar >> (7 - bitPointer++)) & 1;
}
// by passes the current character if we are in the middle of it (used for
// reading bit by bit
void BufferedReader::completeCurrentBit(){
	while(this->bitPointer < 8)
		readBit();
}
void BufferedReader::close(){
	this->~BufferedReader();
}
// returns input stream used
FILE *BufferedReader::getStream(){
	return this->stream;
}
// resets the input , 
// it will seek the file pointer to the start of file
// and it will set the buffer empty
void BufferedReader::reset(){
	fseek(this->stream,0,SEEK_SET);
	this->bufferDataSize = 0;
	this->pointer = 0;
}