// SDIZO2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include <iostream>
#include "AdjacencyListGraph.h"


int main()
{
	////IncidenceMatrixGraph* inc = new IncidenceMatrixGraph("test1.txt", true);
	IncidenceMatrixGraph* inc = new IncidenceMatrixGraph(1, 6, true);
	inc->Dijkstra(1,3);
	
	inc->Print();
	getchar();
	/*AdjacencyListGraph* adjacency = new AdjacencyListGraph(0.25, 4, true);
	adjacency->Print();*/
	/*adjacency->AddEdge(1, 9, 11);
	adjacency->Print();*/
	getchar();
    return 0;
}

