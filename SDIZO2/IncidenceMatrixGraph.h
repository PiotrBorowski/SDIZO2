#pragma once
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
	~IncidenceMatrixGraph();

private:
	State** matrix;
	uint vertices, edges;
	bool directed;
	int* weights;
};

