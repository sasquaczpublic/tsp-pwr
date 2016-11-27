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
				std::cout << value.at(i).at(j) << " ";
			}
			std::cout << std::endl;
		}
	}

};



// TODO: reference additional headers your program requires here
