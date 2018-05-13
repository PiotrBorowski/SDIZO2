// SDIZO2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include <iostream>
#include "AdjacencyListGraph.h"
#include <stack>

void Display(std::pair<int*, int*>, uint);

int main()
{
	//IncidenceMatrixGraph* inc = new IncidenceMatrixGraph("test1.txt", false);
	IncidenceMatrixGraph* inc = new IncidenceMatrixGraph(0.25, 10, false);
	//inc->Print();
	/*Display(inc->Dijkstra(1,8),8);
	Display(inc->Dijkstra(1, 8), 8);*/
	/*IncidenceMatrixGraph *result = inc->Prima();
	result->Print();
	IncidenceMatrixGraph *result2 = inc->Kruskal();
	result2->Print();*/
	//inc->Print();
	//getchar();
	AdjacencyListGraph* adjacency = new AdjacencyListGraph(0.55, 10, false);
	//adjacency->Print();
	//Display(adjacency->Dijkstra(1, 4),4);
	//Display(adjacency->BellmanFord(1, 4), 4);
	AdjacencyListGraph* resultadj = adjacency->Prima();
	resultadj->Print();
	AdjacencyListGraph* resultadj2 = adjacency->Kruskal();
	resultadj2->Print();
	getchar();
    return 0;
}

void Display(std::pair<int*, int*> path, uint dest)
{
	std::cout << std::endl;
	if (path.first == nullptr || path.second == nullptr)
	{
		std::cout << "Nie znaleziono albo ujemny cykl";
			return;
	}
	std::cout << "Droga wynosi: " << path.first[dest] << std::endl;

	std::stack<int> stack;

	for (int j = dest; j > -1; j = path.second[j]) stack.push(j);

	std::cout << "Droga: " << std::endl;
	while (!stack.empty())
	{
		std::cout << stack.top() << "->";
		stack.pop();
	}
	std::cout << std::endl;
}
