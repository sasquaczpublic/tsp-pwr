#pragma once
class TSP
{
public:
	matrix &matrixWithData;
	int lowerBorder;

	TSP(matrix &matrixWithData);
	~TSP();
	void solveProblem();
};

