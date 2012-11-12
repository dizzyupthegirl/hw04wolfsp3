#pragma once
#include "Starbucks.h"

class Node {
public:
    
	Node(Entry* e);
	Node* insert(Entry* e, Node* r, bool isXlevel);
	Entry* search(Entry* key, Node* r, bool isXlevel);
	Node* next(Node* r, bool firstTime);
	Node* previous(Node* r, bool firstTime);
	Node* getlastNode();
    
	// The entry contained within each node
	Entry* key;
	// Show the branches of the tree(if they exist)
	Node* left;
	Node* right;
	Node* lastNode;
	Node* parent;
};