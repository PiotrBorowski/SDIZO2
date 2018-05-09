#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <functional>

typedef std::pair<int, int> iPair;

IncidenceMatrixGraph::IncidenceMatrixGraph()
{
	vertices = 15;
	edges = 15;
	directed = false;
	weights = new int[15];

	//tworzenie matrixa
	matrix = new State*[vertices]; //wierzcholki

	for (uint i = 0; i < vertices; ++i)
	{
		matrix[i] = new State[edges]; //krawedzie
	}

	for (uint i = 0; i < vertices; i++)
		for (uint j = 0; j < edges; j++) matrix[i][j] = NONE;
}

//random
IncidenceMatrixGraph::IncidenceMatrixGraph(float density, uint vertices, bool directed)
{
	this->vertices = vertices;
	this->directed = directed;

	if(directed)
		edges = floor(density * vertices * (vertices - 1));
	else
	{
		edges = floor(density * vertices * (vertices - 1) / 2);
		if (edges < vertices - 1) edges = vertices - 1; // dla spojnosci grafu
	}

	weights = new int[edges];

	//tworzenie matrixa
	matrix = new State*[this->vertices];

	for (uint i = 0; i < vertices; ++i)
	{
		matrix[i] = new State[edges];
	}

	for (uint i = 0; i < this->vertices; i++)
		for (uint j = 0; j < edges; j++) matrix[i][j] = NONE;

	GenerateRandomGraph();
}

IncidenceMatrixGraph::IncidenceMatrixGraph(std::string filename, bool directed)
{
	this->directed = directed;

	std::ifstream file;
	file.open(filename);

	file >> edges;
	file >> vertices;

	uint source, dest;
	int weight;
	weights = new int[edges];
	matrix = new State*[vertices];
	
	//tworzenie matrixa

	for (uint i = 0; i < vertices; ++i)
	{
		matrix[i] = new State[edges];
	}

	for (uint i = 0; i < this->vertices; i++)
		for (uint j = 0; j < edges; j++) matrix[i][j] = NONE;

	while(file >> source >> dest >> weight)
	{
		AddEdge(source, dest, weight);
	}

	file.close();
}


IncidenceMatrixGraph::~IncidenceMatrixGraph()
{
	for (uint i = 0; i < vertices; i++)
	{
		delete[] matrix[i];
	}
	delete[] weights;
}

bool IncidenceMatrixGraph::AddEdge(uint source, uint dest, int weight)
{
	if (source < vertices && dest < vertices && source != dest)
	{
		if (!IsConnected(source, dest)) //sprawdzanie czy dana krawedz juz istenieje
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
			return true;
		}
	}
	return false;
}

void IncidenceMatrixGraph::Print()
{
	std::cout << std::endl;
	std::cout << "  ";
	for (uint i = 0; i < edges; i++)
		std::cout << std::setw(3) << i << " ";
	std::cout << std::endl;
	std::cout << "  ";
	for (uint i = 0; i < edges; i++)
		std::cout << std::setw(3) << weights[i] << " ";

	std::cout << std::endl;

	for (uint row = 0; row < vertices; row++)
	{
		std::cout << row << " ";
		for (uint column = 0; column < edges; column++)
			std::cout << std::setw(3) << matrix[row][column] << " ";
		std::cout << std::endl;
	}
}

int IncidenceMatrixGraph::GetWeight(uint source, uint dest)
{
	for (uint i = 0; i < edges; ++i)
	{
		if (directed)
		{
			if (matrix[source][i] == START)
				if (matrix[dest][i] == END)
					return weights[i];
		}
		else
		{
			if (matrix[source][i] != NONE)
				if (matrix[dest][i] != NONE)
					return weights[i];
		}

	}
	return INT_MAX;
}

void IncidenceMatrixGraph::Dijkstra(uint source, uint dest)
{
	if (source < 0 || dest < 0 || source >= vertices || dest >= vertices)
		return;

	bool * QS = new bool[vertices];
	int * d = new int[vertices];             // Tablica kosztów dojœcia
	int * p = new int[vertices];             // Tablica poprzedników

	

	std::priority_queue< iPair, std::vector <iPair>, std::greater<iPair> > PQ; //kolejka priorytetowa

	for (int i = 0; i < vertices; ++i)
	{
		QS[i] = false;
		d[i] = INT_MAX;
		p[i] = -1;		
		if (i != source) PQ.push(std::make_pair(INT_MAX, i));
	}


	PQ.push(std::make_pair(0, source)); //wstawianie do kolejki
	d[source] = 0;

	while (!PQ.empty())
	{
		int u = PQ.top().second;
		PQ.pop();
		QS[u] = true;

		for (int i = 0; i < vertices; ++i)
		{
			if(!QS[i] && IsConnected(u,i))
			{
				if (d[i] > d[u] + GetWeight(u, i))
				{
					d[i] = d[u] + GetWeight(u, i);
					PQ.push(std::make_pair(d[i], i));
					p[i] = u;
				}
			}
		}
	}

	std::cout << "Droga wynosi: " << d[dest] << std::endl;
	
}

void IncidenceMatrixGraph::GenerateRandomGraph()
{
	srand(time(NULL));

	uint ver1 = 0, ver2 = 0;
	int weight;

	while (ver1 == ver2) 
	{
		ver1 = rand() % vertices;
		ver2 = rand() % vertices;
	}

	weight = rand() % 50;

	AddEdge(ver1, ver2, weight);

	//tworzenie spojnego grafu
	while(existing_edges != edges && existing_edges != vertices - 1)
	{
		do
		{
			ver1 = rand() % vertices;
		} while (!IsConnected(ver1)); //losuje dopoki wylosuje wierzcholek polaczony
		
		do
		{
			ver2 = rand() % vertices;
		} while (IsConnected(ver2)); //losuje dopoki wylosuje wierzcholek niepolaczony

		weight = rand() % 50;
		AddEdge(ver1, ver2, weight);
	}

	//jezeli sa jakies krawedzie do wykrzystania to tworzy nowe krawedzie 
	do
	{
		bool result;
		do {
			ver1 = rand() % vertices;
			ver2 = rand() % vertices;
			weight = rand() % 50;
			result = AddEdge(ver1, ver2, weight); // zeby krawedzie sie nie powtarzaly
		} while (!result);

	}while (existing_edges < edges);
}
//czy wierzcholek posiada polaczenie z innym wierzcholkiem albo jest poczatkiem lub koncem w skierowanym, wykorzystywane do losowania
bool IncidenceMatrixGraph::IsConnected(uint vertex)
{
	for (uint i = 0; i < edges; ++i)
	{
		if (matrix[vertex][i] != NONE)
			return true;
	}
	return false;
}

bool IncidenceMatrixGraph::IsConnected(uint source, uint dest)
{
	for (uint i = 0; i < edges; ++i)
	{
		if(directed)
		{
			if (matrix[source][i] == START)
				if (matrix[dest][i] == END)
					return true;
		}
		else 
		{
			if (matrix[source][i] != NONE)
				if (matrix[dest][i] != NONE)
					return true;
		}
		
	}
	return false;
}

