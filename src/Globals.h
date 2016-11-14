#ifndef __GLOBALS
#define __GLOBALS 1
class Globals{
private:
	Globals(){}
public:
	static const int BUFFERED_READER_BUFFER_SIZE = 0x4000;//4000
	static const int BUFFERED_WRITER_BUFFER_SIZE = BUFFERED_READER_BUFFER_SIZE;
	static const int HUFFMAN_CODE_NUMBER_OF_CHARACTERS = 256; // number of characters
};

void error(const char *message);

#endif
