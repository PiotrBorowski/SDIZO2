#include "stdafx.h"
#include "AdjacencyListGraph.h"
#include <ostream>
#include <iostream>
#include <fstream>
#include <ctime>
#include <queue>
#include <functional>

typedef std::pair<int, int> iPair;

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

AdjacencyListGraph::AdjacencyListGraph(float density, uint vertices, bool directed)
{
	this->vertices = vertices;
	this->directed = directed;
	TableOfLists = new std::list<Edge>[vertices];

	if (directed)
		edges = floor(density * vertices * (vertices - 1));
	else
		edges = floor(density * vertices * (vertices - 1) / 2);


	GenerateRandomGraph();
}


AdjacencyListGraph::~AdjacencyListGraph()
{
	delete[] TableOfLists;
}

bool AdjacencyListGraph::AddEdge(uint source, uint dest, int weight)
{
	if (source < vertices && dest < vertices && source != dest)
	{
		if (!IsConnected(source, dest)) //sprawdzanie czy dana krawedz juz istenieje
		{
			Edge edge;
			edge.weight = weight;
			edge.vertex = dest;

			TableOfLists[source].push_back(edge); //dodajemy z source do dest
			
			if (!directed) //jezeli nieskierowany to trzeba dodac w druga strone
			{
				Edge double_edge;
				double_edge.weight = weight;
				double_edge.vertex = source;
				TableOfLists[dest].push_back(double_edge);
			}
			++existing_edges;
			return true;
		}
	}
	return false;
}

void AdjacencyListGraph::Print()
{
	std::cout << std::endl;

	for (uint i = 0; i < vertices; ++i)
	{
		std::cout << i << "-> ";
		for (Edge element : TableOfLists[i])
		{
			std::cout << element.vertex << ":" << element.weight << "   ";
		}
		std::cout << std::endl;
	}
}

int AdjacencyListGraph::GetWeight(uint source, uint dest)
{
	for (Edge element : TableOfLists[source])
	{
		if (element.vertex == dest)
			return element.weight;
	}
	return INT_MAX;
}

void AdjacencyListGraph::Dijkstra(uint source, uint dest)
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

		for (auto i : TableOfLists[u])
		{
			if (!QS[i.vertex])
			{
				if (d[i.vertex] > d[u] + i.weight)
				{
					d[i.vertex] = d[u] + i.weight;
					PQ.push(std::make_pair(d[i.vertex], i.vertex));
					p[i.vertex] = u;
				}
			}
		}
	}

	std::cout << "Droga wynosi: " << d[dest] << std::endl;
}

//TODO: DIRECTED - FALSE BUG
void AdjacencyListGraph::GenerateRandomGraph()
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
	while (existing_edges != edges && existing_edges != vertices - 1)
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

	} while (existing_edges < edges);
}

//czy wierzcholek posiada polaczenie z innym wierzcholkiem albo jest poczatkiem ub koncem w skierowanym, wykorzystywane do losowania
bool AdjacencyListGraph::IsConnected(uint vertex)
{
	for (uint i = 0; i < vertices; ++i)
	{
		if (IsConnected(i, vertex))
			return false; // jezeli zaden wierzcholek nie jest polaczony z tym wierzcholkiem
	}

	return (TableOfLists[vertex].size() == 0); //i czy wierzcholek nie ma krawedzi
}

bool AdjacencyListGraph::IsConnected(uint source, uint dest)
{
	for (Edge element : TableOfLists[source])
	{
		if (element.vertex == dest)
			return true;
	}
	return false;
}


