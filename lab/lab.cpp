// lab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileReader.h"
#include "TSP.h"
#include <chrono>


int main()
{
	srand(time(NULL));

	matrix costsMatrix;

//	fileReader fileR("tsp4.txt");
//	fileR.read(costsMatrix);
//	//matrixForTests.printMatrix();
//	TSP salesman(costsMatrix);
//	std::cout << "B&B method: " << std::endl;
//	salesman.calculatePath();
//	salesman.clear();
//	std::cout << "brute force method: " << std::endl;
//	salesman.calculatePathByBruteForce();
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	
	std::string filename = "";
	bool mainWhile = true;
	while (mainWhile)
	{
		std::cout << "Podaj nazwe pliku lub 0 aby wyjsc:" << std::endl;
		std::cin >> filename;
		if (filename == "0")
			break;
		fileReader fileR(filename);
		fileR.read(costsMatrix);

		bool mainWhile = true;
		char inputFromUser = '1';
		while(mainWhile)
		{
			std::cout << "Operacje:" << std::endl <<
				"1. Wyswietl macierz kosztow," << std::endl <<
				"2. Wykonaj algorytm B&B," << std::endl <<
				"3. Wykonaj algorytm BF," << std::endl <<
				"4. Wykonaj algorytm B&B a po nim BF," << std::endl <<
				"0. Powrot" << std::endl;
			std::cin >> inputFromUser;
			TSP salesman(costsMatrix);

			switch (inputFromUser)
			{
			case '1':
				salesman.costs.print();
				break;
			case '2':
				start = std::chrono::system_clock::now();
				salesman.calculatePath();
				end = std::chrono::system_clock::now();
				elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				std::cout << "time: " << elapsed.count() << '\n';
				salesman.clear();
				break;
			case '3':
				salesman.calculatePathByBruteForce();
				end = std::chrono::system_clock::now();
				elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				std::cout << "time: " << elapsed.count() << '\n';
				salesman.clear();
				break;
			case '4':
				end = std::chrono::system_clock::now();
				salesman.calculatePath();
				end = std::chrono::system_clock::now();
				elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				std::cout << "time: " << elapsed.count() << '\n';
				salesman.clear();
				end = std::chrono::system_clock::now();
				salesman.calculatePathByBruteForce();
				end = std::chrono::system_clock::now();
				elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				std::cout << "time: " << elapsed.count() << '\n';
				salesman.clear();
				break;
			case '0':
				mainWhile = false;
				break;
			default:

				break;
			}
		}
		
	}

	

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

