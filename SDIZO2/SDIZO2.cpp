// SDIZO2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include <iostream>
#include "AdjacencyListGraph.h"


int main()
{
	//IncidenceMatrixGraph* inc = new IncidenceMatrixGraph("test1.txt", true);
	//IncidenceMatrixGraph* inc = new IncidenceMatrixGraph(0.25, 10, false);
	//inc->Print();
	//inc->Dijkstra(1,8);
	//IncidenceMatrixGraph *result = inc->Prima();
	//result->Print();
	//inc->Print();
	//getchar();
	AdjacencyListGraph* adjacency = new AdjacencyListGraph(0.55, 10, false);
	adjacency->Print();
	//adjacency->Dijkstra(1, 4);
	AdjacencyListGraph* resultadj = adjacency->Prima();
	resultadj->Print();
	getchar();
    return 0;
}

