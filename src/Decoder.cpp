#include "Decoder.h"

/*
	Decode a coded file !
*/

Decoder::Decoder(const char *inputFilename){
	this->br = new BufferedReader(inputFilename);
	printf("Reading header ...\n");
	this->header = new Header(br); // Read header
}

Decoder::~Decoder(){
}

void Decoder::decode(const char *outputFilename){
	printf("Decoding ...\n");
	unsigned int bytesWritten = 0;
	const unsigned int fileSize = header->getFileSize();

	BufferedWriter *bw = new BufferedWriter(outputFilename); // open output
	BSTNode *rootOfTree = header->getRootOfTree(),*currentNode;

	currentNode = rootOfTree; // set DFA start point
	while(true){///*!br->eof() &&*/ bytesWritten < fileSize){
		if(!currentNode->hasChild()){ // if we are at the end of the tree ? then write the character
								      // and go to the root
			bw->writeChar(currentNode->getCharacter());
			currentNode = rootOfTree;
			bytesWritten++;
			if(bytesWritten == fileSize) // is decoding completed ? = output file size = file size in header
				break;
		}
		if(br->readBit() == 1){ // go right
			currentNode = currentNode->getRight();
		} else { // go left
			currentNode = currentNode->getLeft();
		}
		/*
			Same procedure pasted 3 times , its faster , believe it !
		*/
		if(!currentNode->hasChild()){
			bw->writeChar(currentNode->getCharacter());
			currentNode = rootOfTree;
			bytesWritten++;
			if(bytesWritten == fileSize)
				break;
		}
		if(br->readBit() == 1){ // go right
			currentNode = currentNode->getRight();
		} else { // go left
			currentNode = currentNode->getLeft();
		}
		if(!currentNode->hasChild()){
			bw->writeChar(currentNode->getCharacter());
			currentNode = rootOfTree;
			bytesWritten++;
			if(bytesWritten == fileSize)
				break;
		}
		if(br->readBit() == 1){ // go right
			currentNode = currentNode->getRight();
		} else { // go left
			currentNode = currentNode->getLeft();
		}
		if(!currentNode->hasChild()){
			bw->writeChar(currentNode->getCharacter());
			currentNode = rootOfTree;
			bytesWritten++;
			if(bytesWritten == fileSize)
				break;
		}
		if(br->readBit() == 1){ // go right
			currentNode = currentNode->getRight();
		} else { // go left
			currentNode = currentNode->getLeft();
		}
	}
/*	if(br->eof() && bytesWritten < fileSize)
		if(!currentNode->hasChild()){
			bw->writeChar(currentNode->getCharacter());
			currentNode = rootOfTree;
		}*/

	bw->close();
}