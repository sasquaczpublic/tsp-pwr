#pragma once
class TSP
{
public:

	matrix costs;
	salesmanContainer problem;
	bool debug;

	TSP(matrix& costs);
	~TSP();
	void calculateSmallestCost();
	void TSP::solveProblem(matrixWithLB &inputMatrix, matrixWithLB& outputLeftMatrix, matrixWithLB& outputRightMatrix);
	void TSP::calculatePath();
	void TSP::calculateLB();
};

