#include "Encoder.h"

/*
	Encode a file !
*/

Encoder::Encoder(const char *inputFilename){
	this->br = new BufferedReader(inputFilename);
	this->fileSize = 0; // input file size

	printf("Making header ...\n");
	BSTNode **analyzeRes = this->analyzeFile(br); /* Analyze the file to find the no of occurance of characters
													 result will be in an array of nodes */
													

	this->header = new Header();
	header->setFileSize(this->fileSize);

	header->makeTree(analyzeRes); // make the tree from analyze results

	header->generateCharacterBits(); // generate bit strings from tree
}
Encoder::~Encoder(){
}
BSTNode **Encoder::analyzeFile(BufferedReader *br){
	br->reset(); // goto start of file
	unsigned int freq[Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS];
	for(int i = 0 ; i < Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS ; i++)
		freq[i] = 0;
	while(!br->eof()){
		freq[br->readChar()]++;
		this->fileSize++;
	}

	BSTNode **result = new BSTNode*[Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS];
	for(int i = 0 ; i < Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS ; i++){
		BSTNode *c = new BSTNode();
		c->setValue(freq[i]);
		c->setCharacter(i); // make nodes ready for creating a tree !
		result[i] = c;
	}
	return result;
}
void Encoder::encode(const char *outputFilename){
	unsigned int total = 0;
	const unsigned int fileSize = this->fileSize;

	printf("Encoding ...\n");
	br->reset();

	BufferedWriter *bw = new BufferedWriter(outputFilename);
	header->writeHeader(bw); // write header to output file
//	bw->close();
//	return;

	const char **characterBits = (const char**)header->getCharacterBits(); // just to make encoding faster
	const int *characterBitsSizes = (const int*)header->getCharacterBitsSizes();

	while(total < fileSize){//!br->eof()){
		const unsigned char c = br->readChar();
		total++;
		const int len = characterBitsSizes[c]; // get length of bit string for the character c
		const char *bits = characterBits[c]; // get bit string for the character c

		// just to do the writing faster , it is faster , believe it !
		if(len % 2 ==0)
			for(int i = 0 ; i < len ; i+=2){
				bw->writeBit(bits[i]);
				bw->writeBit(bits[i+1]);
			}
		else
			for(int i = 0 ; i < len ; i++)
				bw->writeBit(bits[i]);
	}
	
	bw->close();
	printf("Done.\n");
	printf("Unpacked Size: %u\nPacked Size: %u\nRatio: %0.2f%%\n",this->fileSize,bw->getTotalBytesWritten(),
		((float)bw->getTotalBytesWritten() * 100) / (float) this->fileSize);
//	printf("%u\t%u\n",this->fileSize,bw->getTotalBytesWritten());
}
