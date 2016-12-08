// lab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileReader.h"
#include "TSP.h"


int main()
{
	srand(time(NULL));

	matrix matrixForTests;

	fileReader fileR("tsp5.txt");
	fileR.read(matrixForTests);
	//matrixForTests.printMatrix();
	TSP salesman(matrixForTests);

	salesman.calculatePath();

	

//	std::vector<matrixWithLB> arrayOfMatrix;
//
//	matrixWithLB newSalesman;
//	newSalesman.copyFromMatrix(matrixForTests);
//
//	arrayOfMatrix.push_back(newSalesman);
//
//	matrixWithLB left(arrayOfMatrix.at(0));
//	matrixWithLB right(arrayOfMatrix.at(0));
//	
//	salesman.solveProblem(arrayOfMatrix.at(0), left, right);
//
////
////	left.matrixObject.printMatrix();
////	std::cout << std::endl;
////	std::cout << "lb: " << left.lb << std::endl;
//
//
//	for (int i = 0; i < 2*newSalesman.matrixObject.value.size(); i++)
//	{
//
//		matrixWithLB left(arrayOfMatrix.at(i % 2));
//		matrixWithLB right(arrayOfMatrix.at(i % 2));
//
//		salesman.solveProblem(arrayOfMatrix.at(i % 2), left, right);
//		arrayOfMatrix.push_back(left);
//		arrayOfMatrix.push_back(right);
//	}
//
//
//	for (int i = 0; i < arrayOfMatrix.size(); i++)
//	{
//		arrayOfMatrix.at(i).matrixObject.printMatrix();
//
//
//	
//		std::cout << std::endl;
//		std::cout << "lb: " << arrayOfMatrix.at(i).lb << std::endl;
//	}

	system("pause");

    return 0;
}

