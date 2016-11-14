#pragma once

#include <stdio.h>
#include "Globals.h"
#include "BSTNode.h"

class Heap{
private:
	BSTNode **data;
	int sizeOfData;
	int maxHeapSize;
	int parent(int i);
	int left(int i);
	int right(int i);
	void minHeapify(int i);
	void decreaseKey(int i,BSTNode *key);
	void exchange(int i,int j);
public:
	Heap(BSTNode **data,int sizeOfData);
	BSTNode *getMin();
	BSTNode *extractMin();
	void insert(BSTNode *key);
	int getSize();
};