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
	////IncidenceMatrixGraph* inc = new IncidenceMatrixGraph("test1.txt", false);
	//IncidenceMatrixGraph* inc = new IncidenceMatrixGraph(0.25, 10, false);
	////inc->Print();
	///*Display(inc->Dijkstra(1,8),8);
	//Display(inc->Dijkstra(1, 8), 8);*/
	///*IncidenceMatrixGraph *result = inc->Prima();
	//result->Print();
	//IncidenceMatrixGraph *result2 = inc->Kruskal();
	//result2->Print();*/
	////inc->Print();
	////getchar();
	//AdjacencyListGraph* adjacency = new AdjacencyListGraph(0.55, 10, false);
	////adjacency->Print();
	////Display(adjacency->Dijkstra(1, 4),4);
	////Display(adjacency->BellmanFord(1, 4), 4);
	//AdjacencyListGraph* resultadj = adjacency->Prima();
	//resultadj->Print();
	//AdjacencyListGraph* resultadj2 = adjacency->Kruskal();
	//resultadj2->Print();
	//getchar();

	int choose = 1;
	AdjacencyListGraph* adjacency_list_graph = nullptr;
	IncidenceMatrixGraph* incidence_matrix_graph = nullptr;

	do {
		std::cout << "========================================================\n";
		std::cout << "MENU:\n";
		std::cout << "1. Wczytaj dane z pliku\n";
		std::cout << "2. Wygeneruj graf losowo\n";
		std::cout << "3. Wyswietl graf listowo i macierzowo na ekranie\n";
		std::cout << "4. Dijkstra\n";
		std::cout << "5. Bellman-Ford\n";
		std::cout << "6. Prima\n";
		std::cout << "7. Kruskal\n";
		std::cout << "8. Pomiary czasu\n";
		std::cout << "0. Wyjscie\n";
		std::cout << "========================================================\n";
		std::cin >> choose;



		int directed;
		std::string file;
		switch (choose)
		{
		case 1:

			std::cout << "Graf: 1. Skierowany 2. Nieskierowany";
			std::cin >> directed;
			std::cout << "Nazwa pliku: ";
			std::cin >> file;
			if (directed == 1)
			{
				adjacency_list_graph = new AdjacencyListGraph(file, true);
				incidence_matrix_graph = new IncidenceMatrixGraph(file, true);
			}
			else
			{
				adjacency_list_graph = new AdjacencyListGraph(file, false);
				incidence_matrix_graph = new IncidenceMatrixGraph(file, false);
			}
			break;

		case 2:
			float density;
			uint vertices;
			std::cout << "Liczba wirzcholkow grafu: ";
			std::cin >> vertices;
			std::cout << "Gestosc grafu: ";
			std::cin >> density;
			std::cout << "Graf: 1. Skierowany 2. Nieskierowany";
			std::cin >> directed;
			if (directed == 1)
			{
				adjacency_list_graph = new AdjacencyListGraph(density, vertices, true);
				incidence_matrix_graph = new IncidenceMatrixGraph(density, vertices, true);
			}
			else
			{
				adjacency_list_graph = new AdjacencyListGraph(density, vertices, false);
				incidence_matrix_graph = new IncidenceMatrixGraph(density, vertices, false);
			}
			break;

		case 3:
			if (adjacency_list_graph != nullptr && incidence_matrix_graph != nullptr)
			{
				adjacency_list_graph->Print();
				incidence_matrix_graph->Print();
			}
			break;
		default:
			break;
		}
	} while (choose != 0);
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
