// SDIZO2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include <iostream>


int main()
{
	IncidenceMatrixGraph* inc = new IncidenceMatrixGraph("test1.txt", true);
	inc->Print();
	getchar();
    return 0;
}

