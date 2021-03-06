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
#include <stack>
#include "DisjointSet.h"

typedef std::pair<int, int> iPair; //waga, docelowy
typedef std::pair<int, std::pair<uint, uint>> pPair; //waga, zrodlowy , docelowy

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

IncidenceMatrixGraph::IncidenceMatrixGraph(uint vertices, bool directed)
{
	this->vertices = vertices;
	this->directed = directed;
	if (directed)
		weights = new int[vertices * (vertices - 1)];
	else
		weights = new int[vertices * (vertices - 1) / 2];

	//tworzenie matrixa
	matrix = new State*[vertices]; //wierzcholki

	for (uint i = 0; i < vertices; ++i)
	{
		matrix[i] = new State[vertices * (vertices - 1)]; //krawedzie
	}

	for (uint i = 0; i < vertices; i++)
		for (uint j = 0; j < vertices * (vertices - 1); j++) matrix[i][j] = NONE;
}


//random
IncidenceMatrixGraph::IncidenceMatrixGraph(float density, uint vertices, bool directed)
{
	this->vertices = vertices;
	this->directed = directed;

	if(directed)
		edges = ceil(density * vertices * (vertices - 1));
	else
	{
		edges = ceil(density * vertices * (vertices - 1) / 2);
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
	for (uint i = 0; i < existing_edges; i++)
		std::cout << std::setw(3) << i << " ";
	std::cout << std::endl;
	std::cout << "  ";
	for (uint i = 0; i < existing_edges; i++)
		std::cout << std::setw(3) << weights[i] << " ";

	std::cout << std::endl;

	for (uint row = 0; row < vertices; row++)
	{
		std::cout << row << " ";
		for (uint column = 0; column < existing_edges; column++)
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

std::pair<int*, int*> IncidenceMatrixGraph::Dijkstra(uint source, uint dest)
{
	if (source < 0 || dest < 0 || source >= vertices || dest >= vertices)
		return std::make_pair(nullptr, nullptr);

	bool * QS = new bool[vertices];
	int * d = new int[vertices];             // Tablica koszt�w doj�cia
	int * p = new int[vertices];             // Tablica poprzednik�w

	

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

	delete[] QS;

	return std::make_pair(d, p);
}

std::pair<int*, int*> IncidenceMatrixGraph::BellmanFord(uint source, uint dest)
{
	if (source < 0 || dest < 0 || source >= vertices || dest >= vertices)
		return std::make_pair(nullptr, nullptr);

	int * d = new int[vertices];             // Tablica koszt�w doj�cia
	int * p = new int[vertices];             // Tablica poprzednik�w

	for (int i = 0; i < vertices; ++i)
	{
		d[i] = 100000;
		p[i] = -1;
	}

	d[source] = 0;
	bool no_changes;
	for (int k = 1; k < vertices; ++k)
	{
		no_changes = true;
		for (int i = 0; i < vertices; ++i) // zrodlowe
		{
			for (int j = 0; j < vertices; ++j) //docelowe
			{
				if(IsConnected(i,j))
				{
					if(d[j] > d[i] + GetWeight(i,j))
					{
						no_changes = false;
						d[j] = d[i] + GetWeight(i, j);
						p[j] = i; //poprzednik
					}
				}
			}
		}
		if (no_changes) break;
	}
	
	//sprawdzanie czy nie zawiera ujemnego cyklu
	for (int i = 0; i < vertices; ++i) // zrodlowe
	{
		for (int j = 0; j < vertices; ++j) //docelowe
		{
			if (IsConnected(i, j))
			{
				if (d[j] > d[i] + GetWeight(i, j))
				{
					return std::make_pair(nullptr, nullptr);
				}
			}
		}
	}

	return std::make_pair(d, p);
}

IncidenceMatrixGraph* IncidenceMatrixGraph::Prima()
{
	std::priority_queue< pPair, std::vector <pPair>, std::greater<pPair> > PQ; //kolejka priorytetowa
	bool * visited = new bool[vertices];
	IncidenceMatrixGraph * result = new IncidenceMatrixGraph(vertices, false);
	for (int i = 0; i < vertices; ++i)
	{
		visited[i] = false;
	}

	uint vertex = 0;
	visited[vertex] = true;

	for (int i = 1; i < vertices; ++i)          // Do drzewa dodamy n - 1 kraw�dzi grafu
	{
		for (int i = 0; i < vertices; ++i)
		{
			if (IsConnected(vertex, i) && !visited[i])
			{
				PQ.push(std::make_pair(GetWeight(vertex, i), std::make_pair(vertex, i))); // dodajemy do kolejki krawedz
			}
		}

		pPair edge;
		do
		{
			edge = PQ.top();
			PQ.pop();
		} while (visited[edge.second.second]);

		result->AddEdge(edge.second.first, edge.second.second, edge.first);
		visited[edge.second.second] = true;
		vertex = edge.second.second; //teraz zrodlowym wierzcholkiem jest docelowy
	}

	
	delete[] visited;

	return result;
}

IncidenceMatrixGraph* IncidenceMatrixGraph::Kruskal()
{
	DisjointSet * DSet = new DisjointSet(vertices);
	std::priority_queue< pPair, std::vector <pPair>, std::greater<pPair> > PQ; //kolejka priorytetowa
	IncidenceMatrixGraph * result = new IncidenceMatrixGraph(vertices, false);

	for (int i = 0; i < vertices; ++i)
	{
		DSet->Make_set(i);
	}

	//uzupelnianie kolejki priorytetowej
	for (int i = 0; i < vertices; ++i)
	{
		for (int j = 0; j < vertices; ++j)
		{
			if(IsConnected(i,j))
			{
				PQ.push(std::make_pair(GetWeight(i, j), std::make_pair(i, j)));
			}
		}
	}

	pPair edge;
	for (int i = 1; i < vertices; ++i)
	{
		do
		{
			edge = PQ.top();
			PQ.pop();
		} while (DSet->Find_set(edge.second.first) == DSet->Find_set(edge.second.second));
		result->AddEdge(edge.second.first, edge.second.second, edge.first);
		DSet->Union_sets(edge.second.first, edge.second.second); // laczenie zbiorow
	}
	return result;
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

	weight = rand() % 50 + 1;

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

		weight = rand() % 50 + 1;
		AddEdge(ver1, ver2, weight);
	}

	//jezeli sa jakies krawedzie do wykrzystania to tworzy nowe krawedzie 
	while (existing_edges < edges)
	{
		bool result;
		do {
			ver1 = rand() % vertices;
			ver2 = rand() % vertices;
			weight = rand() % 50 + 1;
			result = AddEdge(ver1, ver2, weight); // zeby krawedzie sie nie powtarzaly
		} while (!result);

	}
}
//czy wierzcholek posiada polaczenie z innym wierzcholkiem albo jest poczatkiem lub koncem w skierowanym, wykorzystywane do losowania
bool IncidenceMatrixGraph::IsConnected(uint vertex)
{
	for (uint i = 0; i < existing_edges; ++i)
	{
		if (matrix[vertex][i] != NONE)
			return true;
	}
	return false;
}

bool IncidenceMatrixGraph::IsConnected(uint source, uint dest)
{
	if (source == dest) return false;
	for (uint i = 0; i < existing_edges; ++i)
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

