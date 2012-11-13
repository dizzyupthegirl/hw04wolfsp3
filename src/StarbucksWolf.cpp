#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "StarbucksWolf.h"
#include "Node.h"
#include <fstream>
#include <iostream>

using namespace ci;
using namespace ci::app;
using namespace std;

void StarbucksWolf::build(Entry* c, int n) {
	vector<Entry> stored_v;

	for(int i = 0; i < n; i++)
		stored_v.push_back(c[i]); 

	// Check for duplicates as defined in class
	for(int j = 0; j < (int)stored_v.size(); j++) {
		for(int k = j + 1; k < (int)stored_v.size(); k++) {
			if(abs(stored_v[j].x - stored_v[k].x) <= 0.00001) {
				if(abs(stored_v[j].y - stored_v[k].y) <= 0.00001)
					stored_v.erase(stored_v.begin() + j);
			}
		}
	}

	// Shuffle, side note: I didn't know till this project that c++ has a shuffler...
	// This makes me very happy...
	std::random_shuffle(stored_v.begin(), stored_v.end());

	Entry* stored_a = new Entry[stored_v.size()];
	for(int y = 0; y < (int)stored_v.size(); y++)
		stored_a[y] = stored_v[y];
	Node* r = NULL;
	for(int i = 0; i < (int)stored_v.size(); i++){
	
		if(i == 0) {
			r = r->insert(&stored_a[i], r, true);
			root = r; // root now points to the root node of the k-d tree
		}
		else
			r->insert(&stored_a[i], r, true);
	}

}

Entry* StarbucksWolf::getNearest(double x, double y) {
	Entry* base = new Entry();
	base->x = x;
	base->y = y;

	Entry* e = root->search(base, root, true);
	Node* lastNode = root->getlastNode();

	Node* node_prev = root->previous(lastNode, true);
	Node* node_next = root->next(lastNode, true);

	Entry* e_prev = node_prev->key;
	Entry* e_next = node_next->key;

	double d1 = sqrt(pow(x - e->x, 2) + pow(y - e->y, 2));
	double d2 = sqrt(pow(x - e_prev->x, 2) + pow(y - e_prev->y, 2));
	double d3 = sqrt(pow(x - e_next->x, 2) + pow(y - e_next->y, 2));

	double min_ = min(d1, min(d2, d3));


	if(min_ == d1)
		return e;
	else if(min_ == d2)
		return e_prev;
	else
		return e_next;
}