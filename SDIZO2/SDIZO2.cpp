// SDIZO2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include <iostream>
#include "AdjacencyListGraph.h"


int main()
{
	IncidenceMatrixGraph* inc = new IncidenceMatrixGraph("test1.txt", true);
	//IncidenceMatrixGraph* inc = new IncidenceMatrixGraph(1, 6, true);
	inc->Dijkstra(1,0);
	
	inc->Print();
	getchar();
	AdjacencyListGraph* adjacency = new AdjacencyListGraph(0.25, 4, false);
	adjacency->Print();
	adjacency->Dijkstra(1,0);
	getchar();
    return 0;
}

