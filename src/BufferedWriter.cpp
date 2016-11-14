#include "BufferedWriter.h"

/*
	BufferedWriter:
		A class for buffering data and writing it.
*/


// use stream for output
BufferedWriter::BufferedWriter(FILE *stream){
	this->initialize(stream);
}
// open file as output
BufferedWriter::BufferedWriter(const char *filename){
	this->initialize(fopen(filename,"wb"));
}

BufferedWriter::~BufferedWriter(void){
	if(this->stream != NULL)
		fclose(this->stream);
	if(this->buffer != NULL)
		delete [] this->buffer;
}

// Initialize variables
void BufferedWriter::initialize(FILE *stream){
	this->pointer = 0; // buffer pointer, when buffer pointer reaches buffer size , buffer is full
	this->bitPointer = 0; // used for writing bit by bit
	this->bufferDataSize = 0; // size of buffer
	this->bitBuffer = 0; // used for writing bit by bit , contains incomplete bits
	this->buffer = new unsigned char[Globals::BUFFERED_WRITER_BUFFER_SIZE];
	if(stream == NULL)
		error("BufferedWriter can't open output file !");
	this->stream = stream;
}
// Writes data to output when buffer is full
void BufferedWriter::writeData(){
	fwrite(this->buffer,1,this->pointer,this->stream);
	this->totalBytesWritten += this->pointer;
	this->pointer = 0; // empty buffer
}
// Write a character to buffer
void BufferedWriter::writeChar(unsigned char c){
	this->buffer[this->pointer++] = c;
	if(this->pointer == Globals::BUFFERED_WRITER_BUFFER_SIZE) // is buffer full ?
		this->writeData();
}
// Write a bit
void BufferedWriter::writeBit(unsigned char bit){
	this->bitBuffer <<= 1;
	bit &= 1;
	this->bitBuffer |= bit;
	this->bitPointer++;

	if(this->bitPointer == 8){ // we have completed a byte ? yes,write it !
		this->writeChar(this->bitBuffer);
		this->bitBuffer = 0; // reset bit pointer
		this->bitPointer = 0; // reset current character
	}
}
void BufferedWriter::close(){
	completeCurrentBits(0);
	this->writeData(); // empty buffer
	this->~BufferedWriter();
}
// Returns the stream used for writing
FILE *BufferedWriter::getStream(){
	return this->stream;
}
// fills the current char if its incomplete
void BufferedWriter::completeCurrentBits(unsigned char toFillBit){
	while(bitPointer != 0)
		writeBit(toFillBit);
}
unsigned int BufferedWriter::getTotalBytesWritten(){
	return this->totalBytesWritten;
}