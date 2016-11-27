#include "stdafx.h"
#include "TSP.h"

TSP::TSP(std::unique_ptr<matrix>& outputMatrixWithData) : outputMatrixWithData(outputMatrixWithData)
{
	
}

TSP::~TSP()
{
}

void TSP::solveProblem()
{
	int min[outputMatrixWithData->size];

	int minCol[rozmiar];
	int minRow[rozmiar];
	int maksymalnyKosztWylaczeniaOdcinka;
	int colToDelete = 0;
	int rowToDelete = 0;;
	bool zeroInCol = false;
	bool zeroInRow = false;

	//wyzerowanie tablicy minimalnych wag
	for (int i = 0; i < rozmiar; i++) {
		min[i] = INT_MAX;
		minCol[i] = INT_MAX;
		minRow[i] = INT_MAX;
	}

	//wyszukanie minimalnych wag dla ka¿dego wiersza
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (m[i][j] >= 0 && m[i][j] < min[i]) {
				min[i] = m[i][j];
			}
		}
		if (min[i] == INT_MAX) {
			min[i] = 0;
		}
		lb += min[i];
	}

	//odjecie minimalnych wag od kazdego elementu
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (m[i][j] > 0) {
				m[i][j] -= min[i];
			}
		}
	}

	//wyzerowanie tablicy minimalnych wag
	for (int i = 0; i < rozmiar; i++) {
		min[i] = INT_MAX;
	}

	//wyszukanie minimalnych wag dla ka¿dej kolumny
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (m[j][i] >= 0 && m[j][i] < min[i]) {
				min[i] = m[j][i];
			}
		}
		if (min[i] == INT_MAX) {
			min[i] = 0;
		}
		lb += min[i];
	}

	//odjecie minimalnych wag od kazdego elementu
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (m[i][j] > 0) {
				m[i][j] -= min[i];
			}
		}
	}

	//Przeszukujemy ka¿dy wiersz i kolumne? w poszukiwaniu najmniejszego elementu (Wartos?c? zero jest pomijane w poszukiwaniach, uwzgle?dnia sie? je dopiero jak wysta?pi co najmniej dwa razy)
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {

			if (m[i][j] >= 0 && m[i][j] < minRow[i]) {
				if (m[i][j] == 0 && !zeroInRow) {
					zeroInRow = true;
				}
				else if (m[i][j] == 0 && zeroInRow) {
					minRow[i] = 0;
				}
				else {
					minRow[i] = m[i][j];
				}
			}

			if (m[j][i] >= 0 && m[j][i] < minCol[i]) {

				if (m[j][i] == 0 && !zeroInCol) {
					zeroInCol = true;
				}
				else if (m[j][i] == 0 && zeroInCol) {
					minCol[i] = 0;
				}
				else {
					minCol[i] = m[j][i];
				}
			}
		}
		zeroInCol = false;
		zeroInRow = false;
	}

	maksymalnyKosztWylaczeniaOdcinka = 0;

	for (int i = 0; i<rozmiar; i++) {
		if (minCol[i] > maksymalnyKosztWylaczeniaOdcinka && minCol[i] < INT_MAX) {
			maksymalnyKosztWylaczeniaOdcinka = minCol[i];
		}

		if (minRow[i] > maksymalnyKosztWylaczeniaOdcinka && minRow[i] < INT_MAX) {
			maksymalnyKosztWylaczeniaOdcinka = minRow[i];
		}
	}

	cout << maksymalnyKosztWylaczeniaOdcinka << endl;

	for (int i = 0; i<rozmiar; i++) {
		for (int j = 0; j<rozmiar; j++) {
			if (m[i][j] == maksymalnyKosztWylaczeniaOdcinka) {
				colToDelete = j;
			}
		}
	}


	for (int i = 0; i<rozmiar; i++) {
		if (m[i][colToDelete] == 0) {
			rowToDelete = i;
		}
	}

	for (int i = 0; i<rozmiar; i++) {
		m[i][colToDelete] = -1;
		m[rowToDelete][i] = -1;
	}

	//    lb += maksymalnyKosztWylaczeniaOdcinka;


	//    for (int i=0; i < rozmiar; i++) {
	//        for (int j=0; j < rozmiar; j++) {
	//            cout << macierz[i][j] << endl;
	//        }
	//    }
	//    
	//    cout << endl;
	//
	//    
	//    for (int i=0; i < rozmiar; i++) {
	//        cout << minCol[i] << endl;
	//    }
	//    cout << endl;
	//    
	//    for (int i=0; i < rozmiar; i++) {
	//        cout << minRow[i] << endl;
	//    }
	cout << lb << endl;
	cout << "-------" << endl;
	
}
