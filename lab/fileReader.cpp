#include "stdafx.h"
#include "fileReader.h"


fileReader::fileReader(std::string fileName)
{
	this->fileName = fileName;
}

fileReader::~fileReader()
{
}

void fileReader::read(matrix &outputMatrixWithData)
{

	std::ifstream fileWithData;
	fileWithData.open(fileName);
	std::string value;
	std::vector<std::string> buffer;
	

	if (!fileWithData.is_open())
		perror("error while opening file");
	while (std::getline(fileWithData, value)) {
		buffer.push_back(value);
	}

	if (fileWithData.bad())
		perror("error while reading file");

	outputMatrixWithData.setSize(std::stoi(buffer.at(0)));

	for (int i = 1; i <= outputMatrixWithData.size; i++)
	{
		std::vector<int> splitedBuffer;
		std::stringstream ss(buffer.at(i));
		std::string tmpBuffer;

		while( ss >> tmpBuffer)
		{
			splitedBuffer.push_back(std::stoi(tmpBuffer));
		}

		if(splitedBuffer.size() != outputMatrixWithData.size)
			perror("error while reading file");

		for (int j = 0; j < outputMatrixWithData.size; j++)
		{
			outputMatrixWithData.value.at(i - 1).at(j) = splitedBuffer.at(j);
		}
	}

}