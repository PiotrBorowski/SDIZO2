#pragma once
#include <vector>

typedef unsigned int uint;

class DisjointSet
{
public:
	std::vector<uint> *parent, *rank;

	DisjointSet(uint n);
	~DisjointSet();
	void Make_set(uint x);
	int Find_set(uint x);
	void Union_sets(uint x, uint y);
private:
	void Link(uint x, uint y);
};

