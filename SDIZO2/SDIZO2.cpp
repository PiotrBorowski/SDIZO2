// SDIZO2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include <iostream>
#include "AdjacencyListGraph.h"
#include <stack>
#include <chrono>

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
		std::cout << "Wybor: ";
		std::cin >> choose;



		int directed;
		std::string file;
		uint source, dest;
		AdjacencyListGraph* adjresult;
		IncidenceMatrixGraph* incresult;
		typedef std::chrono::high_resolution_clock ClockHR;
		std::chrono::time_point<std::chrono::steady_clock> t1, t2;
		long long inctime, adjtime;
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

		case 4:
			if (incidence_matrix_graph != nullptr && adjacency_list_graph != nullptr)
			{
				std::cout << "Podaj wierzcholek startowy: ";
				std::cin >> source;
				std::cout << "Podaj wierzcholek docelowy: ";
				std::cin >> dest;
				std::cout << "\nLista sasiedztwa: \n";
				Display(adjacency_list_graph->Dijkstra(source, dest), dest);
				std::cout << "\nmacierz incydencji: \n";
				Display(incidence_matrix_graph->Dijkstra(source, dest), dest);
			}
				break;

		case 5:
			if (incidence_matrix_graph != nullptr && adjacency_list_graph != nullptr)
			{
				std::cout << "Podaj wierzcholek startowy: ";
				std::cin >> source;
				std::cout << "Podaj wierzcholek docelowy: ";
				std::cin >> dest;
				std::cout << "\nLista sasiedztwa: \n";
				Display(adjacency_list_graph->BellmanFord(source, dest), dest);
				std::cout << "\nmacierz incydencji: \n";
				Display(incidence_matrix_graph->BellmanFord(source, dest), dest);
			}
			break;

		case 6:
			if (incidence_matrix_graph != nullptr && adjacency_list_graph != nullptr)
			{
				adjresult = adjacency_list_graph->Prima();
				incresult = incidence_matrix_graph->Prima();
				adjresult->Print();
				incresult->Print();
				delete adjresult;
				delete incresult;
			}
			break;

		case 7:
			if (incidence_matrix_graph != nullptr && adjacency_list_graph != nullptr)
			{
				adjresult = adjacency_list_graph->Kruskal();
				incresult = incidence_matrix_graph->Kruskal();
				adjresult->Print();
				incresult->Print();
				delete adjresult;
				delete incresult;
			}
			break;

		case 8:
			std::cout << "\nPomiar:\n";
			std::cout << "1. Dijsktra\n";
			std::cout << "2. Bellman-Ford\n";
			std::cout << "3. Prima\n";
			std::cout << "4. Kruskal\n";
			std::cin >> choose;

			switch (choose)
			{
			case 1:
				std::cout << "Wierzcholki: \n";
				std::cin >> vertices;
				inctime = 0;
				adjtime = 0;
				for (density = 0.25; density <= 1; density += 0.25)
				{
					if (density == 1) density = 0.99;
					for (int i = 0; i < 100; ++i)
					{
						incidence_matrix_graph = new IncidenceMatrixGraph(density, vertices, true);
						adjacency_list_graph = new AdjacencyListGraph(density, vertices, true);

						t1 = ClockHR::now();
						incidence_matrix_graph->Dijkstra(rand() % vertices, rand() % vertices);
						t2 = ClockHR::now();
						inctime += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

						t1 = ClockHR::now();
						adjacency_list_graph->Dijkstra(rand() % vertices, rand() % vertices);
						t2 = ClockHR::now();
						adjtime += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

						delete incidence_matrix_graph;
						delete adjacency_list_graph;

					}
					std::cout << "DENSITY " << density << std::endl;
					std::cout << "inc time: " << inctime / 100 << std::endl;
					std::cout << "adj time: " << adjtime / 100 << std::endl;
				}
				break;

			case 2:
				std::cout << "Wierzcholki: \n";
				std::cin >> vertices;
				inctime = 0;
				adjtime = 0;
				for (density = 0.25; density <= 1; density += 0.25)
				{
					if (density == 1) density = 0.99;
					for (int i = 0; i < 100; ++i)
					{
						incidence_matrix_graph = new IncidenceMatrixGraph(density, vertices, true);
						adjacency_list_graph = new AdjacencyListGraph(density, vertices, true);

						t1 = ClockHR::now();
						incidence_matrix_graph->BellmanFord(rand() % vertices, rand() % vertices);
						t2 = ClockHR::now();
						inctime += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

						t1 = ClockHR::now();
						adjacency_list_graph->BellmanFord(rand() % vertices, rand() % vertices);
						t2 = ClockHR::now();
						adjtime += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

						delete incidence_matrix_graph;
						delete adjacency_list_graph;

					}
					std::cout << "DENSITY " << density << std::endl;
					std::cout << "inc time: " << inctime / 100 << std::endl;
					std::cout << "adj time: " << adjtime / 100 << std::endl;
				}
					break;

			case 3:
				std::cout << "Wierzcholki: \n";
				std::cin >> vertices;
				inctime = 0;
				adjtime = 0;
				for (density = 0.25; density <= 1; density += 0.25)
				{
					if (density == 1) density = 0.99;
					for (int i = 0; i < 100; ++i)
					{
						incidence_matrix_graph = new IncidenceMatrixGraph(density, vertices, true);
						adjacency_list_graph = new AdjacencyListGraph(density, vertices, true);

						t1 = ClockHR::now();
						delete incidence_matrix_graph->Prima();
						t2 = ClockHR::now();
						inctime += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

						t1 = ClockHR::now();
						delete adjacency_list_graph->Prima();
						t2 = ClockHR::now();
						adjtime += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

						delete incidence_matrix_graph;
						delete adjacency_list_graph;

					}
					std::cout << "DENSITY " << density << std::endl;
					std::cout << "inc time: " << inctime / 100 << std::endl;
					std::cout << "adj time: " << adjtime / 100 << std::endl;
				}
				break;


			case 4:
				std::cout << "Wierzcholki: \n";
				std::cin >> vertices;
				inctime = 0;
				adjtime = 0;
				for (density = 0.25; density <= 1; density += 0.25)
				{
					if (density == 1) density = 0.99;
					for (int i = 0; i < 100; ++i)
					{
						incidence_matrix_graph = new IncidenceMatrixGraph(density, vertices, true);
						adjacency_list_graph = new AdjacencyListGraph(density, vertices, true);

						t1 = ClockHR::now();
						delete incidence_matrix_graph->Kruskal();
						t2 = ClockHR::now();
						inctime += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

						t1 = ClockHR::now();
						delete adjacency_list_graph->Kruskal();
						t2 = ClockHR::now();
						adjtime += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

						delete incidence_matrix_graph;
						delete adjacency_list_graph;

					}
					std::cout << "DENSITY " << density << std::endl;
					std::cout << "inc time: " << inctime / 100 << std::endl;
					std::cout << "adj time: " << adjtime / 100 << std::endl;
				}
				break;
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
		std::cout << "\nNie znaleziono albo ujemny cykl\n";
			return;
	}

	std::stack<int> stack;

	for (int j = dest; j > -1; j = path.second[j]) stack.push(j);

	if (stack.size() == 1)
	{
		std::cout << "\nBrak sciezki\n";
		return;
	}

	std::cout << "\nDroga wynosi: " << path.first[dest] << std::endl;
	std::cout << "\nDroga: " << std::endl;
	while (!stack.empty())
	{
		std::cout << stack.top() << "->";
		stack.pop();
	}
	std::cout << std::endl;
}
