// lab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileReader.h"
#include "TSP.h"


int main()
{
	matrix matrixForTests;

	fileReader fileR("rbg323.txt");
	fileR.read(matrixForTests);
	//matrixForTests.printMatrix();

	TSP salesman(matrixForTests);
	salesman.solveProblem();

	system("pause");

    return 0;
}

