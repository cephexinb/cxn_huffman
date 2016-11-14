#include "BSTNode.h"

/*
 A Binary Tree Node
 Used for creating huffman code tree.
*/

BSTNode::BSTNode(){
	this->left = this->right = NULL;
	this->value = 0; // = sum of of occurance of its childs | no of occurance on the current character
//	this->character = 0; // this is for terminal nodes, each terminal node is associated with a character in tree
	this->character = -1;
}

void BSTNode::setLeft(BSTNode *left){		
	this->left = left; 
}
void BSTNode::setRight(BSTNode *right){		
	this->right = right; 
}
void BSTNode::setValue(unsigned int value){	this->value = value;}
void BSTNode::setCharacter(char c){			this->character = c;}

BSTNode *BSTNode::getLeft(){				return this->left;}
BSTNode *BSTNode::getRight(){				return this->right;}
unsigned int BSTNode::getValue(){			return this->value;}
char BSTNode::getCharacter(){				return this->character;}

char BSTNode::hasChild(){
	return this->left != NULL || this->right != NULL;
}

bool BSTNode::operator <(BSTNode right){
	return this->value < right.value;
}
bool BSTNode::operator >(BSTNode right){
	return this->value > right.value;
}