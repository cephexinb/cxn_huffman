#include <stdio.h>
#include "Globals.h"

class BSTNode{
private:
	BSTNode *left,*right;
	unsigned int value;
	char character;
public:
	BSTNode();

	void setLeft(BSTNode *left);
	void setRight(BSTNode *right);
	void setValue(unsigned int value);
	void setCharacter(char c);

	BSTNode *getLeft();
	BSTNode *getRight();
	unsigned int getValue();
	char getCharacter();
	char hasChild();

	bool operator <(BSTNode right);
	bool operator >(BSTNode right);
};
