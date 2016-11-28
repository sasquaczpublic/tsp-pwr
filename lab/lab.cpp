// lab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileReader.h"
#include "TSP.h"


int main()
{
	matrix matrixForTests;

	fileReader fileR("tsp5.txt");
	fileR.read(matrixForTests);
	//matrixForTests.printMatrix();

	std::vector<matrixWithLB> arrayOfMatrix;
	TSP salesman;

	matrixWithLB newSalesman;
	newSalesman.copyFromMatrix(matrixForTests);

	arrayOfMatrix.push_back(newSalesman);

	for (int i = 0; i < newSalesman.matrixObject.value.size() - 1; i++)
	{

		matrixWithLB left(arrayOfMatrix.at(i % 2));
		matrixWithLB right(arrayOfMatrix.at(i % 2));

		salesman.solveProblem(arrayOfMatrix.at(i % 2), left, right);
		arrayOfMatrix.push_back(left);
		arrayOfMatrix.push_back(right);
	}


	for (int i = 0; i < arrayOfMatrix.size(); i++)
	{
		arrayOfMatrix.at(i).matrixObject.printMatrix();
		std::cout << std::endl;
	}

	system("pause");

    return 0;
}

