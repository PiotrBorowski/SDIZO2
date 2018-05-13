#include "stdafx.h"
#include "DisjointSet.h"
#include <vector>

using namespace std;


DisjointSet::DisjointSet(uint n)
{
	parent = new std::vector<uint>(n);
	rank = new std::vector<uint>(n);
}


DisjointSet::~DisjointSet()
{
}


void DisjointSet::Make_set(uint x)
{
	parent->at(x) = x;
	rank->at(x) = 0;
}

void DisjointSet::Link(uint x, uint y)
{
	if (rank->at(x) > rank->at(y))
		parent->at(y) = x;
	else
	{
		parent->at(x) = y;
		if (rank->at(x) == rank->at(y))
			++rank->at(y);
	}
}

int DisjointSet::Find_set(uint x)
{
	if (x != parent->at(x))
		parent->at(x) = Find_set(parent->at(x));

	return parent->at(x);
}

void DisjointSet::Union_sets(uint x, uint y)
{
	Link(Find_set(x), Find_set(y));
}
