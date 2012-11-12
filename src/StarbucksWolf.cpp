#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "StarbucksWolf.h"
#include "Node.h"
#include <fstream>
#include <iostream>

using namespace ci;
using namespace ci::app;
using namespace std;

StarbucksWolf::StarbucksWolf() {
	ifstream in("../../../Resources/Starbucks_2006.csv");
	vector <Entry> stored_v;
	string line;
	double i_;
	double j_;
	char separator;
	int x = 0;

	//I was so lost on this part, I'm still not sure exactly how this reads in the code...
	while(in.good()) {
		Entry* e = new Entry();
		stored_v.push_back(*e);
		getline(in, line, ',');

		stored_v[x].identifier = line;
		in >> i_;
		stored_v[x].x = i_;
		in >> separator;//Sam, this is a comma....
		in >> j_;
		stored_v[x].y = j_;
		x++;
	}

	Entry* stored_a = new Entry[stored_v.size()];

	for(int i = 0; i < stored_v.size(); i++)
		stored_a[i] = stored_v[i];
	build(stored_a, stored_v.size());
}


void StarbucksWolf::build(Entry* c, int n) {
	vector<Entry> stored_v;

	for(int i = 0; i < n; i++)
		stored_v.push_back(c[i]); 

	// Check for duplicates as defined in class
	for(int j = 0; j < stored_v.size(); j++) {
		for(int k = j + 1; k < stored_v.size(); k++) {
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
	for(int y = 0; y < stored_v.size(); y++)
		stored_a[y] = stored_v[y];
	Node* r = NULL;
	for(int i = 0; i < stored_v.size(); i++){
	
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