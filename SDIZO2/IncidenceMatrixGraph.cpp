#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include <cmath>
#include <iostream>
#include <iomanip>


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

IncidenceMatrixGraph::IncidenceMatrixGraph(std::string file, bool directed)
{
	this->directed = directed;

}


IncidenceMatrixGraph::~IncidenceMatrixGraph()
{
	for (uint i = 0; i < vertices; i++)
	{
		delete[] matrix[i];
	}
	delete[] weights;
}

void IncidenceMatrixGraph::AddEdge(uint source, uint dest, uint weight)
{
	if (source < vertices && dest < vertices)
	{
		//if (!IsConnected(origin, destination)) //sprawdzanie czy dana krawedz juz istenieje
		{
			if (directed)
			{
				matrix[source][existing_edges] = START;
				matrix[dest][existing_edges] = END;
			}
			else
			{
				matrix[source][existing_edges] = START;
				matrix[dest][existing_edges] = START;
			}

			weights[existing_edges] = weight;
			++existing_edges;
		}
	}
}

void IncidenceMatrixGraph::Print()
{
	std::cout << std::endl;
	std::cout << "  ";
	for (uint i = 0; i < edges; i++)
		std::cout << std::setw(3) << i << " ";

	std::cout << std::endl;

	for (uint row = 0; row < vertices; row++)
	{
		std::cout << row << " ";
		for (uint column = 0; column < edges; column++)
			std::cout << std::setw(3) << matrix[row][column] << " ";
		std::cout << std::endl;
	}
}
