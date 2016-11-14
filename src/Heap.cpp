#include <exception>
#include "Heap.h"

/*
	Min Heap ! Used for creating header
*/

// Create heap from data stored in 'data' , it is character frequencies
Heap::Heap(BSTNode **data,int sizeOfData){
	this->maxHeapSize = sizeOfData;
	this->data = data;
	this->sizeOfData = sizeOfData;

	// build min heap:
	int temp = sizeOfData / 2;
	for(int i = temp ; i >= 0 ; i--)
		minHeapify(i);

	this->sizeOfData = sizeOfData;
}
int Heap::parent(int i){	return (i+1)/2 - 1;		}
int Heap::left(int i){		return 2*(i+1) - 1;		}
int Heap::right(int i){		return left(i) + 1;	}

// Coded from CLRS
void Heap::minHeapify(int i){
	int l = left(i);
	int r = right(i);
	int smallest = 0;
	if(l < this->sizeOfData && *this->data[l] < *this->data[i])
		smallest = l;
	else
		smallest = i;
	if(r < this->sizeOfData && *this->data[r] < *this->data[smallest])
		smallest = r;
	if(smallest != i){
		this->exchange(i,smallest);
		minHeapify(smallest);
	}
}
// Coded from CLRS
BSTNode *Heap::getMin(){
	return this->data[0];
}
// Coded from CLRS
BSTNode *Heap::extractMin(){
	if(this->sizeOfData == 0)
		error("Min heap underflow !");
	BSTNode *min = this->data[0];
	this->data[0] = this->data[this->sizeOfData - 1] ;
	this->sizeOfData--;
	minHeapify(0);
	return min;
}
// Coded from CLRS
void Heap::decreaseKey(int i,BSTNode *key){
/*	if(*key > *this->data[i])
		error("HeapDecreaseKey: new key is bigger than current key");*/
	this->data[i] = key;
	while(i > 0 && *this->data[parent(i)] > *this->data[i]){
		this->exchange(i,parent(i));
		i = parent(i);
	}
}
// Coded from CLRS
void Heap::insert(BSTNode *key){
	if(this->sizeOfData == this->maxHeapSize)
		error("HeapInsert: overflow !");
	this->sizeOfData++;
//	this->data[this->sizeOfData - 1]->setValue(key->getValue()+1);
	decreaseKey(this->sizeOfData - 1,key);
}
// Swap two keys
void Heap::exchange(int i,int j){
	BSTNode *temp = this->data[i];
	this->data[i] = this->data[j];
	this->data[j] = temp;
}
int Heap::getSize(){
	return this->sizeOfData;
}