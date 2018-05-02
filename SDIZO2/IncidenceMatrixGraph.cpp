#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include <cmath>


IncidenceMatrixGraph::IncidenceMatrixGraph()
{
	vertices = 15;
	edges = 15;
	directed = false;
	weights = new int[15];

	matrix = new State*[vertices];

	for (int i = 0; i < vertices; ++i)
	{
		matrix[i] = new State[edges];
	}

	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < edges; j++) matrix[i][j] = NONE;
}

//random
IncidenceMatrixGraph::IncidenceMatrixGraph(float density, uint vertices, bool directed)
{
	this->vertices = vertices;
	edges = floor(density * vertices * (vertices - 1) / 2);
	weights = new int[edges];

	matrix = new State*[this->vertices];

	for (int i = 0; i < this->vertices; i++)
		for (int j = 0; j < edges; j++) matrix[i][j] = NONE;

	//TODO: generowanie spojnego grafu
}


IncidenceMatrixGraph::~IncidenceMatrixGraph()
{
}
