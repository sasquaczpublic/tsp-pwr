#include "stdafx.h"
#include "TSP.h"

TSP::TSP(matrix &matrixWithData) : matrixWithData(matrixWithData)
{
	lowerBorder = 0;
}

TSP::~TSP()
{
}

void TSP::solveProblem()
{
	std::vector<int> min;
	std::vector<int> minCol;
	std::vector<int> minRow;
	min.resize(matrixWithData.size);
	minCol.resize(matrixWithData.size);
	minRow.resize(matrixWithData.size);

	int maksymalnyKosztWylaczeniaOdcinka;
	int colToDelete = 0;
	int rowToDelete = 0;;
	bool zeroInCol = false;
	bool zeroInRow = false;

	//wyzerowanie tablicy minimalnych wag
	for (int i = 0; i < matrixWithData.size; i++) {
		min[i] = INT_MAX;
		minCol[i] = INT_MAX;
		minRow[i] = INT_MAX;
	}

	//wyszukanie minimalnych wag dla ka¿dego wiersza
	for (int i = 0; i < matrixWithData.size; i++) {
		for (int j = 0; j < matrixWithData.size; j++) {
			if (matrixWithData.value[i][j] >= 0 && matrixWithData.value[i][j] < min[i]) {
				min[i] = matrixWithData.value[i][j];
			}
		}
		if (min[i] == INT_MAX) {
			min[i] = 0;
		}
		lowerBorder += min[i];
	}

	//odjecie minimalnych wag od kazdego elementu
	for (int i = 0; i < matrixWithData.size; i++) {
		for (int j = 0; j < matrixWithData.size; j++) {
			if (matrixWithData.value[i][j] > 0) {
				matrixWithData.value[i][j] -= min[i];
			}
		}
	}

	//wyzerowanie tablicy minimalnych wag
	for (int i = 0; i < matrixWithData.size; i++) {
		min[i] = INT_MAX;
	}

	//wyszukanie minimalnych wag dla ka¿dej kolumny
	for (int i = 0; i < matrixWithData.size; i++) {
		for (int j = 0; j < matrixWithData.size; j++) {
			if (matrixWithData.value[j][i] >= 0 && matrixWithData.value[j][i] < min[i]) {
				min[i] = matrixWithData.value[j][i];
			}
		}
		if (min[i] == INT_MAX) {
			min[i] = 0;
		}
		lowerBorder += min[i];
	}

	//odjecie minimalnych wag od kazdego elementu
	for (int i = 0; i < matrixWithData.size; i++) {
		for (int j = 0; j < matrixWithData.size; j++) {
			if (matrixWithData.value[i][j] > 0) {
				matrixWithData.value[i][j] -= min[i];
			}
		}
	}

	//Przeszukujemy ka¿dy wiersz i kolumne? w poszukiwaniu najmniejszego elementu (Wartos?c? zero jest pomijane w poszukiwaniach, uwzgle?dnia sie? je dopiero jak wysta?pi co najmniej dwa razy)
	for (int i = 0; i < matrixWithData.size; i++) {
		for (int j = 0; j < matrixWithData.size; j++) {

			if (matrixWithData.value[i][j] >= 0 && matrixWithData.value[i][j] < minRow[i]) {
				if (matrixWithData.value[i][j] == 0 && !zeroInRow) {
					zeroInRow = true;
				}
				else if (matrixWithData.value[i][j] == 0 && zeroInRow) {
					minRow[i] = 0;
				}
				else {
					minRow[i] = matrixWithData.value[i][j];
				}
			}

			if (matrixWithData.value[j][i] >= 0 && matrixWithData.value[j][i] < minCol[i]) {

				if (matrixWithData.value[j][i] == 0 && !zeroInCol) {
					zeroInCol = true;
				}
				else if (matrixWithData.value[j][i] == 0 && zeroInCol) {
					minCol[i] = 0;
				}
				else {
					minCol[i] = matrixWithData.value[j][i];
				}
			}
		}
		zeroInCol = false;
		zeroInRow = false;
	}

	maksymalnyKosztWylaczeniaOdcinka = 0;

	for (int i = 0; i<matrixWithData.size; i++) {
		if (minCol[i] > maksymalnyKosztWylaczeniaOdcinka && minCol[i] < INT_MAX) {
			maksymalnyKosztWylaczeniaOdcinka = minCol[i];
		}

		if (minRow[i] > maksymalnyKosztWylaczeniaOdcinka && minRow[i] < INT_MAX) {
			maksymalnyKosztWylaczeniaOdcinka = minRow[i];
		}
	}

	//3std::cout << maksymalnyKosztWylaczeniaOdcinka << std::endl;

	for (int i = 0; i<matrixWithData.size; i++) {
		for (int j = 0; j<matrixWithData.size; j++) {
			if (matrixWithData.value[i][j] == maksymalnyKosztWylaczeniaOdcinka) {
				colToDelete = j;
			}
		}
	}


	for (int i = 0; i<matrixWithData.size; i++) {
		if (matrixWithData.value[i][colToDelete] == 0) {
			rowToDelete = i;
		}
	}

	for (int i = 0; i<matrixWithData.size; i++) {
		matrixWithData.value[i][colToDelete] = -1;
		matrixWithData.value[rowToDelete][i] = -1;
	}

	//    lowerBorder += maksymalnyKosztWylaczeniaOdcinka;


	//    for (int i=0; i < matrixWithData.size; i++) {
	//        for (int j=0; j < matrixWithData.size; j++) {
	//            cout << macierz[i][j] << endl;
	//        }
	//    }
	//    
	//    cout << endl;
	//
	//    
	//    for (int i=0; i < matrixWithData.size; i++) {
	//        cout << minCol[i] << endl;
	//    }
	//    cout << endl;
	//    
	//    for (int i=0; i < matrixWithData.size; i++) {
	//        cout << minRow[i] << endl;
	//    }
	std::cout << "Lower border is: " << lowerBorder << std::endl;
	std::cout << "-------" << std::endl;
	
}
