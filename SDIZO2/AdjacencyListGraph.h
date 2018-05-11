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
	AdjacencyListGraph(uint vertices, bool directed);
	AdjacencyListGraph(std::string filename, bool directed);
	AdjacencyListGraph(float density, uint vertices, bool directed);
	~AdjacencyListGraph();
	bool AddEdge(uint source, uint dest, int weight);
	void Print();
	int GetWeight(uint source, uint dest);
	void Dijkstra(uint source, uint dest);
	AdjacencyListGraph* Prima();
private:
	std::list<Edge> *TableOfLists;
	uint vertices, edges, existing_edges;
	bool directed;

	void GenerateRandomGraph();
	bool IsConnected(uint vertex);
	bool IsConnected(uint source, uint dest);
};

