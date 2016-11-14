#pragma once

#include <stdio.h>
#include <string.h>
#include "Globals.h"
#include "BSTNode.h"
#include "Heap.h"
#include "BufferedWriter.h"
#include "BufferedReader.h"
#include "Queue.h"

class Header{
private:
	char **characterBits;
	int *characterBitsSizes;
	unsigned int fileSize;

	BSTNode *rootOfTree;

	void writeTreeStructure(BufferedWriter *bw);
	void writeTree(BufferedWriter *bw);

	BSTNode *readTreeStructure(BufferedReader *bw);
	void readHeader(BufferedReader *bw);

public:
	Header();
	Header(BufferedReader *br);

	void makeTree(BSTNode **fileAnalyzeResult);
	void generateCharacterBits();
	void generateCharacterBits(char *prefix,BSTNode *root);
	void setFileSize(unsigned int fileSize);

	int *getCharacterBitsSizes();
	unsigned int getFileSize();
	char **getCharacterBits();
	BSTNode *getRootOfTree();

	void writeHeader(BufferedWriter *bw);

};
