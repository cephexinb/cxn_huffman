#include "Queue.h"

/*
	A FIFO queue, used for implementing BFS algorithm
	while reading/writing header to/from file
*/
Queue::Queue(){
	this->count = 0;
	this->head = this->tail = NULL;
}

void Queue::enQ(BSTNode *node){
	count++;
	QBSTNode *newNode = new QBSTNode();
	newNode->data = node;

	if(head == NULL){
		head = tail = newNode;
	} else {
		tail->next = newNode;
		tail = tail->next;
	}
	tail->next = NULL;
}

BSTNode *Queue::deQ(){
	if(count == 0)
		error("Queue is empty !");
	count--;
	BSTNode *result = head->data;
	QBSTNode *temp = head;

	head = head->next;

	delete temp;

	if(count == 0){
		head = tail = NULL;
	}
	return result;
}

int Queue::getCount(){ return this->count; }
