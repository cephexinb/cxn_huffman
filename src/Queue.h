#pragma once

#include <stdio.h>
#include "Globals.h"
#include "BSTNode.h"

struct QBSTNode {
	QBSTNode *next;
	BSTNode *data;
};

class Queue{
private:
	QBSTNode *head,*tail;
	int count;
public:
	Queue();
	void enQ(BSTNode *node);
	BSTNode *deQ();
	int getCount();
};