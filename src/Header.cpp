#include "Header.h"

/*
	A class used for reading/writing/making header
*/

Header::Header(){
	this->characterBits = new char*[Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS]; // character bit strings
	this->characterBitsSizes = new int[Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS]; // character bit strings lengths

	for(int i = 0 ; i < Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS ; i++){
		this->characterBits[i] = new char[Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS];
		this->characterBitsSizes[i] = 0;
	}
	this->rootOfTree = NULL;
}

// Read header from file
Header::Header(BufferedReader *br){
	// br->reset();
	this->characterBits = new char*[Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS];
	this->characterBitsSizes = new int[Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS];

	for(int i = 0 ; i < Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS ; i++){
		this->characterBits[i] = new char[Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS];
		this->characterBitsSizes[i] = 0;
	}
	readHeader(br);
	generateCharacterBits(); // generate character bit strings from read data
}

void Header::readHeader(BufferedReader *br){
	this->fileSize = 0;
	FILE *stream = br->getStream();
	fread(&this->fileSize,4,1,stream); // read file size
	this->rootOfTree = readTreeStructure(br); // read tree structure
	Queue *q = new Queue(); // Use BFS algorithm to read data , look at writeHeader
	q->enQ(this->rootOfTree);
	while(q->getCount() > 0){
		BSTNode *node = q->deQ();
		if(node->hasChild()){ // if current node has childs , enQ its childs so the childs would be able
							//   to read data
			q->enQ(node->getLeft());
			q->enQ(node->getRight());
		} else {
			node->setCharacter(br->readChar()); // if it has no child , so it should have a character
											//     associated with it , read it !
		}
	}
}

// Read the structure of a tree
BSTNode *Header::readTreeStructure(BufferedReader *br){
	BSTNode *root = new BSTNode();
	Queue *q = new Queue();

	q->enQ(root);
	// Use BFS algorithm for reading tree structure
	while(q->getCount() > 0){
		BSTNode *c = q->deQ();
		unsigned char bit = br->readBit();
		if(bit){ // if it has childs , allocate nodes and enQ childs so they would be able to read their data
			BSTNode *newNode = new BSTNode();
			c->setLeft(newNode);
			q->enQ(newNode);

			newNode = new BSTNode();
			c->setRight(newNode);
			q->enQ(newNode);
		}
	}
	br->completeCurrentBit(); // = by pass one bit, 511 -> 512
	return root;
}

// Makes a optimized tree from frequency of characters
void Header::makeTree(BSTNode **fileAnalyzeResult){
	Heap *h = new Heap(fileAnalyzeResult,Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS);

	int n = Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS;
	// I coded these parts from the book !
	for(int i = 0 ; i < n - 1; i++){
		BSTNode *newNode = new BSTNode();
		BSTNode *left = h->extractMin();
		BSTNode *right = h->extractMin();
		newNode->setValue(left->getValue() + right->getValue());
		newNode->setLeft(left);
		newNode->setRight(right);
		h->insert(newNode);
	}
	this->rootOfTree = h->extractMin();
//	return this->rootOfTree;
}
// Generate bit strings from tree
void Header::generateCharacterBits(){

	char *prefix = new char[Globals::HUFFMAN_CODE_NUMBER_OF_CHARACTERS]; // current code, used for parsing tree
	strcpy(prefix,"");
	generateCharacterBits(prefix,this->rootOfTree); // recursivly find all strings
	delete [] prefix;
}
void Header::generateCharacterBits(char *prefix,BSTNode *root){
	if(root->hasChild()){ /* if it has childs recursively try to find the strings */
		strcat(prefix,"0"); // If we go left we have a 0 at the end of our code
		generateCharacterBits(prefix,root->getLeft());

		prefix[strlen(prefix)-1] = '1'; // If we go left we have a 1 at the end of our code
		generateCharacterBits(prefix,root->getRight());
		prefix[strlen(prefix)-1] = 0; // Clean the last character, we are going up on the tree!
	} else { // It has no child, it means that we have find a code, we will save it
//		static int a = 0;
		unsigned int len = (unsigned int)strlen(prefix); // number of bits = depth of node - 1
//		a+=len;
		unsigned char currentChar = root->getCharacter();
		for(unsigned int i = 0 ; i < len ; i++)
			this->characterBits[currentChar][i] = prefix[i] - '0'; // set the bits
		this->characterBitsSizes[currentChar] = len; // set the length
	}
}

char **Header::getCharacterBits(){
	return this->characterBits;
}

int *Header::getCharacterBitsSizes(){
	return this->characterBitsSizes;
}

// Write header to a BufferedWriter
void Header::writeHeader(BufferedWriter *bw){
	FILE *stream = bw->getStream();
	fwrite(&this->fileSize,4,1,stream); // write file size
	writeTree(bw); // Write tree
}

void Header::writeTree(BufferedWriter *bw){
	writeTreeStructure(bw); // Write tree structure

	/* Use BFS algorithm to write data ,
	   First the root is inserted to queue, then
	   if the first node in the queue has childs we enq it
	   so we will be able to find its data , 
	   Otherwise write the character associated with it */
	Queue *q = new Queue();
	q->enQ(this->rootOfTree);
	while(q->getCount() > 0){
		BSTNode *node = q->deQ();
		if(node->hasChild()){
			q->enQ(node->getLeft());
			q->enQ(node->getRight());
		} else {
			bw->writeChar(node->getCharacter());
		}
	}
}
// Writes tree structure to a BufferedWriter
void Header::writeTreeStructure(BufferedWriter *bw){
	/* Use BFS to write data */
	Queue *q = new Queue();
	q->enQ(this->rootOfTree);
	while(q->getCount() > 0){
		BSTNode *node = q->deQ();
		if(node->hasChild()){
			q->enQ(node->getLeft());
			q->enQ(node->getRight());
			bw->writeBit(1);
		} else {
			bw->writeBit(0);
		}
	}
	bw->completeCurrentBits(0); // write 512 bits instead of 511 bits
}

void Header::setFileSize(unsigned int fileSize){
	this->fileSize = fileSize;
}
unsigned int Header::getFileSize(){
	return this->fileSize;
}
BSTNode *Header::getRootOfTree(){
	return this->rootOfTree;
}