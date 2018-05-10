// SDIZO2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include <iostream>
#include "AdjacencyListGraph.h"


int main()
{
	//IncidenceMatrixGraph* inc = new IncidenceMatrixGraph("test1.txt", true);
	/*IncidenceMatrixGraph* inc = new IncidenceMatrixGraph(0.25, 10, false);
	inc->Print();
	inc->Dijkstra(1,8);*/
	
	//inc->Print();
	getchar();
	AdjacencyListGraph* adjacency = new AdjacencyListGraph("test1.txt", true);
	//adjacency->Print();
	adjacency->Dijkstra(1,6);
	getchar();
    return 0;
}

