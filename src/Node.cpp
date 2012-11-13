#include "Node.h"

Node::Node(Entry* e) {
	key = e;
	left = NULL;
	right = NULL;
	population=NULL;
	r=rand()%256;
	g=rand()%256;
	b=rand()%256;
}



Entry* Node::search(Entry* key, Node* current, bool isXlevel) {
	Entry* closest;
	if(current == NULL)
		return NULL;

	if((key->x == current->key->x)&&( key->y == current->key->y)) {
		lastNode = current;
		return current->key;
	}

	if(isXlevel) {
		if(key->x <= current->key->x) {
			if(current->left == NULL) {
				closest = current->key;
				lastNode = current;
			}
			else {
				parent = current;
				closest = search(key, current->left, !isXlevel);
			}
		}
		else {
			if(current->right == NULL) {
				closest = current->key;
				lastNode = current;
			}
			else {
				parent = current;
				closest = search(key, current->right, !isXlevel);
			}
		}
	}
	else {
		if(key->y <= current->key->y) {
			if(current->left == NULL) {
				closest = current->key;
				lastNode = current;
			}
			else {
				parent = current;
				closest = search(key, current->left, !isXlevel);
			}
		}
		else {
			if(current->right == NULL) {
				closest = current->key;
				lastNode = current;
			}
			else {
				parent = current;
				closest= search(key, current->right, !isXlevel);
			}
		}
	}

	return closest;
}


Node* Node::insert(Entry* e, Node* current, bool isXlevel) {
	if(current == NULL)
		return new Node(e);
	if(current->key == e)
		return current;
	if(isXlevel) {
		if(e->x <= current->key->x) {
			if(current->left != NULL)
				current->left = insert(e, current->left, !isXlevel);
			else
				current->left = new Node(e);
		}
		else if(e->x > current->key->x) {
			if(current->right != NULL)
				current->right = insert(e, current->right, !isXlevel);
			else
				current->right = new Node(e);
		}
	}
	else {
		if(e->y <= current->key->y) {
			if(current->left != NULL)
				current->left = insert(e, current->left, !isXlevel);
			else
				current->left = new Node(e);
		}
		else if(e->y > current->key->y) {
			if(current->right != NULL)
				current->right = insert(e, current->right, !isXlevel);
			else
				current->right = new Node(e);
		}
	}

	return current;
}


Node* Node::next(Node* current, bool firstTime) {
	Node* next_node;

	if(current->right == NULL && current->left != NULL)
		return parent;

	if(current->right == NULL && current->left == NULL)
		return current;

	if(current->right->left != NULL && firstTime)
		next_node = next(current->right, false);
	else if(current->left != NULL)
		next_node = next(current->left, false);
	else
		next_node = current->right;

	return next_node;

}

Node* Node::previous(Node* current, bool firstTime) {
	Node* prev_node;


	if(current->left == NULL && current->right != NULL)
		return parent;
	if(current->left == NULL && current->right == NULL)
		return current;

	if(current->left->right != NULL && firstTime)
		prev_node = next(current->left, false);
	else if(current->right != NULL)
		prev_node = next(current->right, false);
	else
		prev_node = current->left;

	return prev_node;	
}

Node* Node::getlastNode() {
	return lastNode;
}