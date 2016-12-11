#include "stdafx.h"
#include "TSP.h"
#include <list>
#include <queue>
#include <iterator>

TSP::TSP(matrix& pathCosts)
{
	debug = false;
	costs = pathCosts;
	timesToCheckBestPath = 10;
	
	calculateSmallestCost();

	std::list<int> avaliableNodes;

	for (int i = 0; i < costs.value.size(); i++)
	{
		avaliableNodes.push_back(i);
	}

	for (int i = 0; i < costs.value.size(); i++)
	{
		std::vector<path> startPath{};
		avaliableNodes.remove(i);
		problem.problems.push(problemNode(startPath, avaliableNodes, i));
		avaliableNodes.push_back(i);
	}
		
}

void TSP::clear()
{
	while (problem.problems.size())
		problem.problems.pop();

	std::list<int> avaliableNodes;

	for (int i = 0; i < costs.value.size(); i++)
	{
		avaliableNodes.push_back(i);
	}

	for (int i = 0; i < costs.value.size(); i++)
	{
		std::vector<path> startPath{};
		avaliableNodes.remove(i);
		problem.problems.push(problemNode(startPath, avaliableNodes, i));
		avaliableNodes.push_back(i);
	}
}

TSP::~TSP()
{
}

void TSP::calculateSmallestCost()
{
	for (int choiceBest = 0; choiceBest < timesToCheckBestPath; choiceBest++)
	{
		std::list<int> avaliableNodes;
		std::list<int>::iterator pathAvaliableIterator;

		for (int i = 0; i < costs.value.size(); i++)
		{
			avaliableNodes.push_back(i);
		}

		pathAvaliableIterator = avaliableNodes.begin();

		int nextNode = INT32_MAX;
		nextNode = rand() % avaliableNodes.size();
		std::advance(pathAvaliableIterator, nextNode);
		nextNode = *pathAvaliableIterator;

		std::vector<path> startPath{};
		avaliableNodes.remove(nextNode);
		problem.problems.push(problemNode(startPath, avaliableNodes, nextNode));
		
		while (true)
		{
			if (problem.problems.empty())
				break;
			problemNode currentProblem = problem.problems.front();
			pathAvaliableIterator = currentProblem.pathAvaliable.begin();
			problem.problems.pop();
			nextNode = INT32_MAX;

			if (currentProblem.pathAvaliable.empty())
			{
				int cost = costs.value.at(currentProblem.currentNode).at(currentProblem.pathUntilNow.front().from);
				if (debug) std::cout << "SMALLEST? min:current " << problem.smallestCost << ":" << currentProblem.LB + cost << std::endl;
				if (currentProblem.LB + cost < problem.smallestCost)
				{
					problem.smallestCost = currentProblem.LB + cost;
					std::vector<path> newPath = currentProblem.pathUntilNow;
					newPath.push_back(path(currentProblem.currentNode, currentProblem.pathUntilNow.front().from));
					problem.bestPath = problemNode(newPath, std::list<int>(), currentProblem.pathUntilNow.front().from, currentProblem.LB + cost);
					if (debug) std::cout << "START LB:" << std::endl;
					if (debug) problem.bestPath.print();
				}
				continue;
			}

			nextNode = rand() % currentProblem.pathAvaliable.size();
			std::advance(pathAvaliableIterator, nextNode);
			nextNode = *pathAvaliableIterator;
			int cost = costs.value.at(currentProblem.currentNode).at(nextNode);
			if (currentProblem.LB + cost < problem.smallestCost)
			{
				std::vector<path> newPath = currentProblem.pathUntilNow;
				newPath.push_back(path(currentProblem.currentNode, nextNode));
				currentProblem.pathAvaliable.remove(nextNode);
				problem.problems.push(problemNode(newPath, currentProblem.pathAvaliable, nextNode, currentProblem.LB + cost));
			}
		}
	}
}

void TSP::calculateLB()
{
	
}

void TSP::calculatePath()
{
	int j {0}, k{0};
	while (true)
	{
		if (problem.problems.empty())
			break;
		problemNode currentProblem = problem.problems.front();
		//std::list<int>::iterator pathAvaliableIterator;
		problem.problems.pop();
		

		if (currentProblem.pathAvaliable.empty())
		{
			int cost = costs.value.at(currentProblem.currentNode).at(currentProblem.pathUntilNow.front().from);
			if (debug) std::cout << "SMALLEST? min:current " << problem.smallestCost << ":" << currentProblem.LB + cost << std::endl;
			++k;
			if (currentProblem.LB + cost < problem.smallestCost)
			{
				problem.smallestCost = currentProblem.LB + cost;
				std::vector<path> newPath = currentProblem.pathUntilNow;
				newPath.push_back(path(currentProblem.currentNode, currentProblem.pathUntilNow.front().from));
				problem.bestPath = problemNode(newPath, currentProblem.pathAvaliable, currentProblem.pathUntilNow.front().from, currentProblem.LB + cost);

			}
			continue;
		}

		int nextNode = INT32_MAX;

		for (int i = 0; i <= currentProblem.pathAvaliable.size(); i++)
		{
			//int nextNode = rand() % currentProblem.pathAvaliable.size();
			nextNode = currentProblem.pathAvaliable.front();
			currentProblem.pathAvaliable.pop_front();
			int cost = costs.value.at(currentProblem.currentNode).at(nextNode);
			if (currentProblem.LB + cost < problem.smallestCost)
			{
				std::vector<path> newPath = currentProblem.pathUntilNow;
				newPath.push_back(path(currentProblem.currentNode, nextNode));
				
				problem.problems.push(problemNode(newPath, currentProblem.pathAvaliable, nextNode, currentProblem.LB + cost));
				
			}
			currentProblem.pathAvaliable.push_back(nextNode);
		}
		if (debug) std::cout << "===========================================" << std::endl << "while: " << ++j << std::endl << "===========================================" << std::endl;
		if (debug) currentProblem.print();
	}

	std::cout << "Best: " << std::endl << k << " times checked, whether it is the best path, and used " << timesToCheckBestPath << " random paths" << std::endl;
	problem.bestPath.print();

}


void TSP::calculatePathByBruteForce()
{
	int j{ 0 }, k{ 0 };
	while (true)
	{
		if (problem.problems.empty())
			break;
		problemNode currentProblem = problem.problems.front();
		//std::list<int>::iterator pathAvaliableIterator;
		problem.problems.pop();


		if (currentProblem.pathAvaliable.empty())
		{
			int cost = costs.value.at(currentProblem.currentNode).at(currentProblem.pathUntilNow.front().from);
			if (debug) std::cout << "SMALLEST? min:current " << problem.smallestCost << ":" << currentProblem.LB + cost << std::endl;
			++k;
			if (currentProblem.LB + cost < problem.smallestCost)
			{
				problem.smallestCost = currentProblem.LB + cost;
				std::vector<path> newPath = currentProblem.pathUntilNow;
				newPath.push_back(path(currentProblem.currentNode, currentProblem.pathUntilNow.front().from));
				problem.bestPath = problemNode(newPath, currentProblem.pathAvaliable, currentProblem.pathUntilNow.front().from, currentProblem.LB + cost);

			}
			continue;
		}

		int nextNode = INT32_MAX;

		for (int i = 0; i <= currentProblem.pathAvaliable.size(); i++)
		{
			//int nextNode = rand() % currentProblem.pathAvaliable.size();
			nextNode = currentProblem.pathAvaliable.front();
			currentProblem.pathAvaliable.pop_front();
			int cost = costs.value.at(currentProblem.currentNode).at(nextNode);

			std::vector<path> newPath = currentProblem.pathUntilNow;
			newPath.push_back(path(currentProblem.currentNode, nextNode));

			problem.problems.push(problemNode(newPath, currentProblem.pathAvaliable, nextNode, currentProblem.LB + cost));


			currentProblem.pathAvaliable.push_back(nextNode);
		}
		if (debug) std::cout << "===========================================" << std::endl << "while: " << ++j << std::endl << "===========================================" << std::endl;
		if (debug) currentProblem.print();
	}

	std::cout << "Best: " << std::endl << k << " times checked, whether it is the best path" << std::endl;
	problem.bestPath.print();

}






void TSP::solveProblem(matrixWithLB &inputMatrix, matrixWithLB& outputLeftMatrix, matrixWithLB& outputRightMatrix)
{
	std::vector<int> min;
	std::vector<int> minCol;
	std::vector<int> minRow;
	min.resize(inputMatrix.matrixObject.size);
	minCol.resize(inputMatrix.matrixObject.size);
	minRow.resize(inputMatrix.matrixObject.size);
	
	int maksymalnyKosztWylaczeniaOdcinka;
	int colToDelete = 0;
	int rowToDelete = 0;;
	bool zeroInCol = false;
	bool zeroInRow = false;

	//wyzerowanie tablicy minimalnych wag
	for (int i = 0; i < inputMatrix.matrixObject.size; i++) {
		min[i] = INT_MAX;
		minCol[i] = INT_MAX;
		minRow[i] = INT_MAX;
	}

	//wyszukanie minimalnych wag dla ka¿dego wiersza
	for (int i = 0; i < inputMatrix.matrixObject.size; i++) {
		for (int j = 0; j < inputMatrix.matrixObject.size; j++) {
			if (inputMatrix.matrixObject.value[i][j] >= 0 && inputMatrix.matrixObject.value[i][j] < min[i]) {
				min[i] = inputMatrix.matrixObject.value[i][j];
			}
		}
		if (min[i] == INT_MAX) {
			min[i] = 0;
		}
		outputLeftMatrix.lb += min[i];
		outputRightMatrix.lb += min[i];
	}

	//odjecie minimalnych wag od kazdego elementu
	for (int i = 0; i < inputMatrix.matrixObject.size; i++) {
		for (int j = 0; j < inputMatrix.matrixObject.size; j++) {
			if (inputMatrix.matrixObject.value[i][j] > 0) {
				outputLeftMatrix.matrixObject.value[i][j] -= min[i];
				outputRightMatrix.matrixObject.value[i][j] -= min[i];
			}
		}
	}

	//wyzerowanie tablicy minimalnych wag
	for (int i = 0; i < outputLeftMatrix.matrixObject.size; i++) {
		min[i] = INT_MAX;
	}

	//wyszukanie minimalnych wag dla ka¿dej kolumny
	for (int i = 0; i < outputLeftMatrix.matrixObject.size; i++) {
		for (int j = 0; j < outputLeftMatrix.matrixObject.size; j++) {
			if (outputLeftMatrix.matrixObject.value[j][i] >= 0 && outputLeftMatrix.matrixObject.value[j][i] < min[i]) {
				min[i] = outputLeftMatrix.matrixObject.value[j][i];
			}
		}
		if (min[i] == INT_MAX) {
			min[i] = 0;
		}
		outputLeftMatrix.lb += min[i];
		outputRightMatrix.lb += min[i];
	}

	//odjecie minimalnych wag od kazdego elementu
	for (int i = 0; i < outputLeftMatrix.matrixObject.size; i++) {
		for (int j = 0; j < outputLeftMatrix.matrixObject.size; j++) {
			if (outputLeftMatrix.matrixObject.value[i][j] > 0) {
				outputLeftMatrix.matrixObject.value[i][j] -= min[i];
				outputRightMatrix.matrixObject.value[i][j] -= min[i];
			}
		}
	}



	//Przeszukujemy ka¿dy wiersz i kolumne? w poszukiwaniu najmniejszego elementu (Wartos?c? zero jest pomijane w poszukiwaniach, uwzgle?dnia sie? je dopiero jak wysta?pi co najmniej dwa razy)
	for (int i = 0; i < outputLeftMatrix.matrixObject.size; i++) {
		for (int j = 0; j < outputLeftMatrix.matrixObject.size; j++) {

			if (outputLeftMatrix.matrixObject.value[i][j] >= 0 && outputLeftMatrix.matrixObject.value[i][j] < minRow[i]) {
				if (outputLeftMatrix.matrixObject.value[i][j] == 0 && !zeroInRow) {
					zeroInRow = true;
				}
				else if (outputLeftMatrix.matrixObject.value[i][j] == 0 && zeroInRow) {
					minRow[i] = 0;
				}
				else {
					minRow[i] = outputLeftMatrix.matrixObject.value[i][j];
				}
			}

			if (outputLeftMatrix.matrixObject.value[j][i] >= 0 && outputLeftMatrix.matrixObject.value[j][i] < minCol[i]) {

				if (outputLeftMatrix.matrixObject.value[j][i] == 0 && !zeroInCol) {
					zeroInCol = true;
				}
				else if (outputLeftMatrix.matrixObject.value[j][i] == 0 && zeroInCol) {
					minCol[i] = 0;
				}
				else {
					minCol[i] = outputLeftMatrix.matrixObject.value[j][i];
				}
			}
		}
		zeroInCol = false;
		zeroInRow = false;
	}

	maksymalnyKosztWylaczeniaOdcinka = 0;

	for (int i = 0; i<outputLeftMatrix.matrixObject.size; i++) {
		if (minCol[i] > maksymalnyKosztWylaczeniaOdcinka && minCol[i] < INT_MAX) {
			maksymalnyKosztWylaczeniaOdcinka = minCol[i];
		}

		if (minRow[i] > maksymalnyKosztWylaczeniaOdcinka && minRow[i] < INT_MAX) {
			maksymalnyKosztWylaczeniaOdcinka = minRow[i];
		}
	}

	//3std::cout << maksymalnyKosztWylaczeniaOdcinka << std::endl;

	for (int i = 0; i<outputLeftMatrix.matrixObject.size; i++) {
		for (int j = 0; j<outputLeftMatrix.matrixObject.size; j++) {
			if (outputLeftMatrix.matrixObject.value[i][j] == maksymalnyKosztWylaczeniaOdcinka) {
				colToDelete = j;
			}
		}
	}


	for (int i = 0; i<outputLeftMatrix.matrixObject.size; i++) {
		if (outputLeftMatrix.matrixObject.value[i][colToDelete] == 0) {
			rowToDelete = i;
		}
	}

	for (int i = 0; i<outputLeftMatrix.matrixObject.size; i++) {
		outputLeftMatrix.matrixObject.value[i][colToDelete] = -1;
		outputLeftMatrix.matrixObject.value[rowToDelete][i] = -1;
	}

	outputLeftMatrix.matrixObject.value[colToDelete][rowToDelete] = -1;
	outputRightMatrix.matrixObject.value[colToDelete][rowToDelete] = -1;
	outputRightMatrix.lb += maksymalnyKosztWylaczeniaOdcinka;

//
//	inputMatrix.matrixObject.printMatrix();
//
//	std::cout << std::endl;
//	std::cout << "Lower border is: " << inputMatrix.lb << std::endl;
//	std::cout << "-------" << std::endl;
	
}
