#pragma once
class TSP
{
public:

	matrix costs;
	salesmanContainer problem;
	bool debug;
	int timesToCheckBestPath;

	TSP(matrix& costs);
	void clear();
	~TSP();
	void calculateSmallestCost();
	void TSP::solveProblem(matrixWithLB &inputMatrix, matrixWithLB& outputLeftMatrix, matrixWithLB& outputRightMatrix);
	void TSP::calculatePath();
	void TSP::calculatePathByBruteForce();
	void TSP::calculateLB();
};

