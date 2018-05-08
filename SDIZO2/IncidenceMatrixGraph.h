#pragma once
#include <string>
typedef unsigned int uint;

class IncidenceMatrixGraph
{
	enum State
	{
		START = 1,
		END = -1,
		NONE = 0
	};

public:
	IncidenceMatrixGraph();
	IncidenceMatrixGraph(float density, uint vertices, bool directed);
	IncidenceMatrixGraph(std::string file, bool directed);
	~IncidenceMatrixGraph();
	bool AddEdge(uint source, uint dest, int weight);
	void Print();
	int GetWeight(uint source, uint dest);

private:
	State** matrix;
	uint vertices, edges, existing_edges;
	bool directed;
	int* weights;

	void GenerateRandomGraph();
	bool IsConnected(uint vertex);
	bool IsConnected(uint source, uint dest);
};

