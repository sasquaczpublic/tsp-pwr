#pragma once
#include <string>
#include <sstream>

class fileReader
{
public:
	std::string fileName;
	std::fstream file;
	fileReader(std::string fileName);
	~fileReader();
	void read(matrix &outputMatrixWithData);
};

