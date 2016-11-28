#include "stdafx.h"
#include "TSP.h"

TSP::TSP()
{

}

TSP::~TSP()
{
}

void TSP::solveProblem(matrixWithLB &inputMatrix, matrixWithLB& outputLeftMatrix, matrixWithLB& outputRightMatrix)
{
	std::vector<int> min;
	std::vector<int> minCol;
	std::vector<int> minRow;
	min.resize(inputMatrix.matrixObject.size);
	minCol.resize(inputMatrix.matrixObject.size);
	minRow.resize(inputMatrix.matrixObject.size);
	
	int maksymalnyKosztWylaczeniaOdcinka;
	int colToDelete = 0;
	int rowToDelete = 0;;
	bool zeroInCol = false;
	bool zeroInRow = false;

	//wyzerowanie tablicy minimalnych wag
	for (int i = 0; i < inputMatrix.matrixObject.size; i++) {
		min[i] = INT_MAX;
		minCol[i] = INT_MAX;
		minRow[i] = INT_MAX;
	}

	//wyszukanie minimalnych wag dla ka¿dego wiersza
	for (int i = 0; i < inputMatrix.matrixObject.size; i++) {
		for (int j = 0; j < inputMatrix.matrixObject.size; j++) {
			if (inputMatrix.matrixObject.value[i][j] >= 0 && inputMatrix.matrixObject.value[i][j] < min[i]) {
				min[i] = inputMatrix.matrixObject.value[i][j];
			}
		}
		if (min[i] == INT_MAX) {
			min[i] = 0;
		}
		outputLeftMatrix.lb += min[i];
		outputRightMatrix.lb += min[i];
	}

	//odjecie minimalnych wag od kazdego elementu
	for (int i = 0; i < inputMatrix.matrixObject.size; i++) {
		for (int j = 0; j < inputMatrix.matrixObject.size; j++) {
			if (inputMatrix.matrixObject.value[i][j] > 0) {
				outputLeftMatrix.matrixObject.value[i][j] -= min[i];
				outputRightMatrix.matrixObject.value[i][j] -= min[i];
			}
		}
	}

	//wyzerowanie tablicy minimalnych wag
	for (int i = 0; i < outputLeftMatrix.matrixObject.size; i++) {
		min[i] = INT_MAX;
	}

	//wyszukanie minimalnych wag dla ka¿dej kolumny
	for (int i = 0; i < outputLeftMatrix.matrixObject.size; i++) {
		for (int j = 0; j < outputLeftMatrix.matrixObject.size; j++) {
			if (outputLeftMatrix.matrixObject.value[j][i] >= 0 && outputLeftMatrix.matrixObject.value[j][i] < min[i]) {
				min[i] = outputLeftMatrix.matrixObject.value[j][i];
			}
		}
		if (min[i] == INT_MAX) {
			min[i] = 0;
		}
		outputLeftMatrix.lb += min[i];
		outputRightMatrix.lb += min[i];
	}

	//odjecie minimalnych wag od kazdego elementu
	for (int i = 0; i < outputLeftMatrix.matrixObject.size; i++) {
		for (int j = 0; j < outputLeftMatrix.matrixObject.size; j++) {
			if (outputLeftMatrix.matrixObject.value[i][j] > 0) {
				outputLeftMatrix.matrixObject.value[i][j] -= min[i];
				outputRightMatrix.matrixObject.value[i][j] -= min[i];
			}
		}
	}



	//Przeszukujemy ka¿dy wiersz i kolumne? w poszukiwaniu najmniejszego elementu (Wartos?c? zero jest pomijane w poszukiwaniach, uwzgle?dnia sie? je dopiero jak wysta?pi co najmniej dwa razy)
	for (int i = 0; i < outputLeftMatrix.matrixObject.size; i++) {
		for (int j = 0; j < outputLeftMatrix.matrixObject.size; j++) {

			if (outputLeftMatrix.matrixObject.value[i][j] >= 0 && outputLeftMatrix.matrixObject.value[i][j] < minRow[i]) {
				if (outputLeftMatrix.matrixObject.value[i][j] == 0 && !zeroInRow) {
					zeroInRow = true;
				}
				else if (outputLeftMatrix.matrixObject.value[i][j] == 0 && zeroInRow) {
					minRow[i] = 0;
				}
				else {
					minRow[i] = outputLeftMatrix.matrixObject.value[i][j];
				}
			}

			if (outputLeftMatrix.matrixObject.value[j][i] >= 0 && outputLeftMatrix.matrixObject.value[j][i] < minCol[i]) {

				if (outputLeftMatrix.matrixObject.value[j][i] == 0 && !zeroInCol) {
					zeroInCol = true;
				}
				else if (outputLeftMatrix.matrixObject.value[j][i] == 0 && zeroInCol) {
					minCol[i] = 0;
				}
				else {
					minCol[i] = outputLeftMatrix.matrixObject.value[j][i];
				}
			}
		}
		zeroInCol = false;
		zeroInRow = false;
	}

	maksymalnyKosztWylaczeniaOdcinka = 0;

	for (int i = 0; i<outputLeftMatrix.matrixObject.size; i++) {
		if (minCol[i] > maksymalnyKosztWylaczeniaOdcinka && minCol[i] < INT_MAX) {
			maksymalnyKosztWylaczeniaOdcinka = minCol[i];
		}

		if (minRow[i] > maksymalnyKosztWylaczeniaOdcinka && minRow[i] < INT_MAX) {
			maksymalnyKosztWylaczeniaOdcinka = minRow[i];
		}
	}

	//3std::cout << maksymalnyKosztWylaczeniaOdcinka << std::endl;

	for (int i = 0; i<outputLeftMatrix.matrixObject.size; i++) {
		for (int j = 0; j<outputLeftMatrix.matrixObject.size; j++) {
			if (outputLeftMatrix.matrixObject.value[i][j] == maksymalnyKosztWylaczeniaOdcinka) {
				colToDelete = j;
			}
		}
	}


	for (int i = 0; i<outputLeftMatrix.matrixObject.size; i++) {
		if (outputLeftMatrix.matrixObject.value[i][colToDelete] == 0) {
			rowToDelete = i;
		}
	}

	for (int i = 0; i<outputLeftMatrix.matrixObject.size; i++) {
		outputLeftMatrix.matrixObject.value[i][colToDelete] = -1;
		outputLeftMatrix.matrixObject.value[rowToDelete][i] = -1;
	}

	outputLeftMatrix.matrixObject.value[colToDelete][rowToDelete] = -1;
	outputRightMatrix.matrixObject.value[colToDelete][rowToDelete] = -1;
	outputRightMatrix.lb += maksymalnyKosztWylaczeniaOdcinka;


	//    lowerBorder += maksymalnyKosztWylaczeniaOdcinka;


	//    for (int i=0; i < outputLeftMatrix.matrixObject.size; i++) {
	//        for (int j=0; j < outputLeftMatrix.matrixObject.size; j++) {
	//            cout << macierz[i][j] << endl;
	//        }
	//    }
	//    
	//    cout << endl;
	//
	//    
	//    for (int i=0; i < outputLeftMatrix.matrixObject.size; i++) {
	//        cout << minCol[i] << endl;
	//    }
	//    cout << endl;
	//    
	//    for (int i=0; i < outputLeftMatrix.matrixObject.size; i++) {
	//        cout << minRow[i] << endl;
	//    }
	std::cout << "Lower border is: " << outputLeftMatrix.lb << std::endl;
	std::cout << "-------" << std::endl;
	
}
