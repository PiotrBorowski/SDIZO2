#pragma once
#include <list>

typedef unsigned int uint;

struct Edge
{
	uint vertex;
	int weight;
};

class AdjacencyListGraph
{
public:
	AdjacencyListGraph();
	AdjacencyListGraph(std::string filename, bool directed);
	AdjacencyListGraph(float density, uint vertices, bool directed);
	~AdjacencyListGraph();
	void AddEdge(uint source, uint dest, int weight);
	void Print();
private:
	std::list<Edge> *TableOfLists;
	uint vertices, edges;
	bool directed;
	int* weights;
};

