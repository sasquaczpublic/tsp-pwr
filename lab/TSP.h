#pragma once
class TSP
{
public:
	matrix &matrixWithData;
	const int size;

	TSP(matrix &matrixWithData);
	~TSP();
	void solveProblem();
};

