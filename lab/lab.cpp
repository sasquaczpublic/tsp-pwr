// lab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileReader.h"


int main()
{
	auto matrixForTests{ std::make_unique<matrix>() };

	fileReader fileR("input.txt");
	fileR.read(matrixForTests);
	matrixForTests->printMatrix();

    return 0;
}

