#pragma once
class TSP
{
public:
	std::unique_ptr<matrix>& outputMatrixWithData;

	TSP(std::unique_ptr<matrix>& outputMatrixWithData);
	~TSP();
	void solveProblem();
};

