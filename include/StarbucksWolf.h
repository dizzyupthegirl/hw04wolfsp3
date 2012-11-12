#pragma once
#include <string>
#include "Starbucks.h"
#include "Node.h"
using namespace std;


class StarbucksWolf : public Starbucks
{
public:
	StarbucksWolf();
	~StarbucksWolf(void);

	Node* root;

	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
};