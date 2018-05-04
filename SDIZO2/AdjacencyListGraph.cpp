#include "stdafx.h"
#include "AdjacencyListGraph.h"
#include <ostream>
#include <iostream>
#include <fstream>


AdjacencyListGraph::AdjacencyListGraph()
{
	vertices = 15;
	edges = 15;
	directed = false;
	TableOfLists = new std::list<Edge>[vertices];
}

AdjacencyListGraph::AdjacencyListGraph(std::string filename, bool directed)
{
	this->directed = directed;

	std::ifstream file;
	file.open(filename);

	file >> edges;
	file >> vertices;

	TableOfLists = new std::list<Edge>[vertices];

	uint source, dest, weight;
	while (file >> source >> dest >> weight)
	{
		AddEdge(source, dest, weight);
	}
}


AdjacencyListGraph::~AdjacencyListGraph()
{
	delete[] TableOfLists;
}

void AdjacencyListGraph::AddEdge(uint source, uint dest, uint weight)
{
	Edge edge;
	edge.weight = weight;
	edge.vertex = dest;

	TableOfLists[source].push_back(edge);
}

void AdjacencyListGraph::Print()
{
	std::cout << std::endl;

	for (int i = 0; i < vertices; ++i)
	{
		std::cout << i << ": ";
		for (Edge element : TableOfLists[i])
		{
			std::cout << element.vertex << " ";
		}
		std::cout << std::endl;
	}
}


