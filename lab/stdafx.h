// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <string.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <iomanip>

struct matrix
{
	std::vector<std::vector<int>> value;
	int size;

	void setMatrix(int size)
	{
		this->size = size;
		value.resize(size);
		for (int i = 0; i < size; i++)
		{
			value.at(i).resize(size);
		}
	}

	void printMatrix()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				std::cout << std::setw(3);
				std::cout << value.at(i).at(j) << " ";
			}
			std::cout << std::endl;
		}
	}

	matrix()
	{		
	}

	matrix(const matrix & matrixToCopy)
	{
		setMatrix(matrixToCopy.size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				value.at(i).at(j) = matrixToCopy.value.at(i).at(j);
			}
		}
	}

};

struct matrixWithLB
{
	matrix matrixObject;
	int lb;
	
	matrixWithLB()
	{
		
	}

	matrixWithLB(const matrixWithLB& matrixToCopy)
	{
		matrixObject = matrix(matrixToCopy.matrixObject);
		lb = matrixToCopy.lb;
	}

	void copyFromMatrix(const matrix& matrixToCopy)
	{
		matrixObject = matrix(matrixToCopy);
		lb = 0;
	}
};



// TODO: reference additional headers your program requires here
