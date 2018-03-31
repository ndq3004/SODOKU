// ConsoleApplication13.cpp : Defines the entry point for the console application.
// SODOKU

#include "stdafx.h"
#include <iostream>
#include <fstream>
#define S 9
#include <string>

using namespace std;
struct zeroArr
{
	int row;
	int col;
};
void readFile(const char *name, int SDK[S][S], struct zeroArr *Zr_Arr, int &Zr) {
	fstream f;
	f.open(name, ios::in);
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			f >> SDK[i][j];
			if (SDK[i][j] == 0) {
				Zr_Arr[Zr].row = i;
				Zr_Arr[Zr++].col = j;
			}
		}
	}
	f.close();
}

bool checkLast(zeroArr *Zr_Arr, int &Zr, int i, int j) {
	if (Zr_Arr[Zr - 1].row == i && Zr_Arr[Zr - 1].col == j)
	{
		return true;
	}
	return false;
}

int Num_Available(int *Arr, int SDK[S][S], int row, int col) {
	//Arr will contain the available number 
	int *A = new int[S + 1];
	for (int i = 1; i <= S; i++) A[i] = 0;
	//check Numbers exist in row having SDK[row][col]  
	for (int i = 0; i < S; i++) {
		if (SDK[row][i]) A[SDK[row][i]] = 1;
	}
	//check Numbers exist in column having SDK[row][col]  
	for (int j = 0; j < S; j++) {
		if (SDK[j][col]) A[SDK[j][col]] = 1;
	}
	//check Numbers exist in 9-square square having SDK[row][col]
	for (int i = 3 * (row / 3); i < (3 * (row / 3) + 3); i++) {
		for (int j = 3 * (col / 3); j < (3 * (col / 3) + 3); j++) {
			if (SDK[i][j]) A[SDK[i][j]] = 1;
		}
	}
	int k = 0;
	for (int i = 1; i <= S; i++) {
		if (A[i] == 0) Arr[k++] = i;
	}
	return k;
}

void print(int SDK[S][S]) {
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < S; j++)
			cout << SDK[i][j] << "  ";
		cout << endl;
	}
}

void SODOKU(int SDK[][S], struct zeroArr Zr_Arr[S*S], int Zr, int dem) {
		int i = Zr_Arr[dem].row;
		int j = Zr_Arr[dem].col;
		if (SDK[i][j] == 0) {
			int *Avail = new int[S];
			int count;
			count = Num_Available(Avail, SDK, i, j);
			if (count)
			{
				for (int g = 0; g < count; g++) {
					SDK[i][j] = Avail[g];
					if (checkLast(Zr_Arr, Zr, i, j)) print(SDK);
					else { SODOKU(SDK, Zr_Arr, Zr, dem + 1); SDK[i][j] = 0; }
				}
			}//endifCount
			 { delete[] Avail; }
		}
	}




int main() {
	/*int **SDK = new int*[S];
	for (int i = 0; i < S; i++) {
	SDK[i] = new int[S];
	}*/
	int SDK[S][S], Zr = 0;
	struct zeroArr Zr_Arr[S*S];
	int dem = 0;
	readFile("sodoku.txt", SDK, Zr_Arr, Zr);
	print(SDK);
	cout << endl;
	SODOKU(SDK, Zr_Arr, Zr, dem);
	return 0;
}


