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
#include <list>
#include <queue>

struct path
{
	int from, to;

	path()
	{
		from = to = -1;
	}

	path(int from, int to)
	{
		this->from = from;
		this->to = to;
	}

};

struct matrix
{
	std::vector<std::vector<int>> value;
	int size;

	void setSize(int size)
	{
		this->size = size;
		value.resize(size);
		for (int i = 0; i < size; i++)
		{
			value.at(i).resize(size);
		}
	}

	void print()
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
		setSize(matrixToCopy.size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				value.at(i).at(j) = matrixToCopy.value.at(i).at(j);
			}
		}
	}

};

struct problemNode
{
	std::vector<path> pathUntilNow;
	std::list<int> pathAvaliable;
	int LB;
	int currentNode;

	problemNode()
	{
		LB = 0;
	}

	problemNode(std::vector<path> untilNow, std::list<int> avaliable, int nodeNo)
	{
		pathUntilNow = untilNow;
		pathAvaliable = avaliable;
		LB = 0;
		currentNode = nodeNo;
	}

	problemNode(std::vector<path> untilNow, std::list<int> avaliable, int nodeNo, int newLB)
	{
		pathUntilNow = untilNow;
		pathAvaliable = avaliable;
		LB = newLB;
		currentNode = nodeNo;
	}

	void print()
	{
		std::cout << "crr: " << currentNode << " lb: " << LB << std::endl << "path: ";
		for (int i = 0; i < pathUntilNow.size(); i++)
		{
			std::cout << pathUntilNow.at(i).from << "->" << pathUntilNow.at(i).to << ", ";
		}
		std::cout << std::endl << "avlb: ";
		std::list<int>::iterator pathAvaliableIterator {pathAvaliable.begin()};
		for (int i = 0; i < pathAvaliable.size(); i++)
		{
			std::cout << *pathAvaliableIterator << ", ";
			std::advance(pathAvaliableIterator, 1);
		}
		std::cout << std::endl;
	}

};

struct salesmanContainer
{
	matrix costs;
	int smallestCost;
	int mediumCost;
	std::queue<problemNode> problems;
	problemNode bestPath;

	salesmanContainer()
	{
		smallestCost = INT32_MAX;
		mediumCost = INT32_MAX;
	}

	void print()
	{
		int queueSize = problems.size();
		problemNode tmpProblem;
		for (int i = 0; i < queueSize; i++)
		{
			tmpProblem = problems.front();
			problems.pop();
			problems.push(tmpProblem);
			std::cout << "--------------------------------------------------" << std::endl;
			tmpProblem.print();
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
