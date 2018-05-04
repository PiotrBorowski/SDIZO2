// SDIZO2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include <iostream>
#include "AdjacencyListGraph.h"


int main()
{
	IncidenceMatrixGraph* inc = new IncidenceMatrixGraph("test1.txt", true);
	inc->Print();
	inc->AddEdge(1, 9, 11);
	inc->Print();

	AdjacencyListGraph* adjacency = new AdjacencyListGraph("test1.txt", true);
	adjacency->Print();
	adjacency->AddEdge(1, 9, 11);
	adjacency->Print();
	getchar();
    return 0;
}

