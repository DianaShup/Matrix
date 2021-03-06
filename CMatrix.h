#pragma once
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
template <typename T>
class CMatrix
{
private:
	int WIERSZY;
	int KOLUMNY;
	T** matrix;
public:
	CMatrix() {}

	//+
	CMatrix(int wierszy, int kolumny) {
		allocateMatrixMemory(wierszy, kolumny);
	}

	// +конструктор копирования
	CMatrix(CMatrix& matrix2)
	{
		allocateMatrixMemory(matrix2.WIERSZY, matrix2.KOLUMNY);
		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < KOLUMNY; j++) {
				matrix[i][j] = matrix2[i][j];
			}
		}

	}
private:

	//+
	void clearMatrix() {
		for (int i = 0; i < WIERSZY; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		KOLUMNY = 0;
		WIERSZY = 0;
		matrix = nullptr;
	}

	//+
	void allocateMatrixMemory(int wierszy, int kolumny) {
		WIERSZY = wierszy;
		KOLUMNY = kolumny;
		matrix = new T*[wierszy];
		for (int i = 0; i < wierszy; i++) {
			matrix[i] = new T[kolumny];
		}

	}
public:

	//+
	~CMatrix() {
		clearMatrix();


	}

	//+ print
	void mPrint() {
		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < KOLUMNY; j++) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";

		}
	}

	//dodawanie macierzy +---------------------------------------------------
	CMatrix operator+(CMatrix &matrix2) {
		CMatrix  res_matrix(WIERSZY, KOLUMNY);
		if (KOLUMNY != matrix2.KOLUMNY && WIERSZY != matrix2.WIERSZY) {
			res_matrix.Fill();
			return res_matrix;
		}
		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < KOLUMNY; j++) {
				(res_matrix[i][j]) = matrix[i][j] + matrix2[i][j];
			}
		}
		return res_matrix;

	}

	//+ оператор присвоения
	CMatrix& operator=(const CMatrix &matrix2) {
		if (this == &matrix2)
			return *this;
		clearMatrix();
		allocateMatrixMemory(matrix2.WIERSZY, matrix2.KOLUMNY);

		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < KOLUMNY; j++) {
				matrix[i][j] = matrix2[i][j];
			}
		}
		return *this;

	}

	//+odejmowanie macierzy --------------------------------------------
	CMatrix operator-(CMatrix &matrix2) {
		CMatrix res_matrix(WIERSZY, KOLUMNY);
		if (KOLUMNY != matrix2.KOLUMNY && WIERSZY != matrix2.WIERSZY) {
			res_matrix.Fill();
			return res_matrix;
		}
		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < KOLUMNY; j++) {
				res_matrix[i][j] = matrix[i][j] - matrix2[i][j];
			}
		}
		return res_matrix;
	}

	//+mnożenie macierzy przez liczbę ---------------------------------------------------
	CMatrix operator*(T liczba) {
		CMatrix res_matrix(WIERSZY, KOLUMNY);
		if (liczba == 0) {
			res_matrix.Fill();
			return res_matrix;
		}

		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < KOLUMNY; j++) {
				res_matrix[i][j] = liczba * matrix[i][j];
			}
		}
		return res_matrix;
	}
	//+заполнение матрицы нулями
	void Fill() {
		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < KOLUMNY; j++) {
				matrix[i][j] = 0;
			}
		}

	}
	//возвращает указатель на ячейку-----------------------------------
	T* operator[]( int elem) { return matrix[elem]; }
	const T* operator[](int elem) const { return matrix[elem]; };

	//+transponowanie macierzy------------------------------------------
	CMatrix getmTransponate() {
		CMatrix temp_matrix(KOLUMNY, WIERSZY);

		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < KOLUMNY; j++) {
				temp_matrix[j][i] = matrix[i][j];
			}
		}

		return temp_matrix;
	}

	//+mnożenie przez wektor---------------------- poprawic
	T* multiplyVector(T* vector, int lenght) {
		if (lenght != KOLUMNY) {
			return nullptr;
		}
		T* result = new T[lenght];
		for (int i = 0; i < WIERSZY; i++) {
			T sum = 0;
			for (int j = 0; j < KOLUMNY; j++) {
				sum += matrix[i][j] * vector[j];
			}
			result[i] = sum;
		}
		return result;
	}

	//+mnożenie macierzy przez macierz ---------
	CMatrix multiplyMatrix(CMatrix<T> matrix2) {
		CMatrix res_matrix(WIERSZY, matrix2.KOLUMNY);
		if (KOLUMNY != matrix2.WIERSZY) {
			res_matrix.Fill();
			return res_matrix;
		}

		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < matrix2.KOLUMNY; j++) {
				res_matrix[i][j] = 0;
				for (int k = 0; k < KOLUMNY; k++)
				{
					res_matrix[i][j] += matrix[i][k] * matrix2[k][j];
				}
			}
		}
		return res_matrix;

	}
	//CMatrix operator*=(CMatrix &matrix2) {
	//	CMatrix res_matrix(WIERSZY, matrix2.KOLUMNY);
	//	if (KOLUMNY != matrix2.WIERSZY || WIERSZY != matrix2.KOLUMNY) {
	//		res_matrix.Fill();
	//		return res_matrix;
	//	}

	//	for (int i = 0; i < WIERSZY; i++) {
	//		for (int j = 0; j < matrix2.KOLUMNY; j++) {
	//			res_matrix[i][j] = 0;
	//			for (int k = 0; k < KOLUMNY; k++)
	//			{
	//				res_matrix[i][j] += matrix[i][k] * matrix2[k][j];
	//				
	//			}
	//		}
	//	}
	//	return res_matrix;
	//}
	/*CMatrix operator*=(CMatrix &matrix2) {
		CMatrix res_matrix(WIERSZY, matrix2.KOLUMNY);
		if (KOLUMNY != matrix2.WIERSZY || WIERSZY != matrix2.KOLUMNY) {
			res_matrix.Fill();
			return res_matrix;
		}

		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < matrix2.KOLUMNY; j++) {
				res_matrix[i][j] = 0;
				for (int k = 0; k < KOLUMNY; k++)
				{
					res_matrix[i][j] += matrix[i][k] * matrix2[k][j];
				}
			}
		}
		*this = res_matrix;
		return  *this;
	}*/

	CMatrix operator*=(CMatrix &matrix2) {
		if (KOLUMNY != matrix2.WIERSZY) {
			return *this;
		}

		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < matrix2.KOLUMNY; j++) {
				T x = 0;
				for (int k = 0; k < KOLUMNY; k++)
				{
					x += matrix[i][k] * matrix2[k][j];
				}
				matrix[i][j] = x;
			}
		}
		return  *this;
	}

	//+wczytywanie z pliku ---------------
	void readFromFile(const char*filename) {
		int rows = 0;
		string line;
		fstream input(filename);
		while (getline(input, line))
			rows++;

		int kols = 0;
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == ' ') {
				kols++;
			}
		}
		input.clear();
		input.seekg(0);

		allocateMatrixMemory(rows, kols + 1);
		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < KOLUMNY; j++) {
				input >> matrix[i][j];
			}
		}


	}
	//+ создать вектор из строки
	T* createVectorFromRow(int wiersz) {
		if (wiersz<0 || wiersz>WIERSZY) {
			return nullptr;
		}
		T* result = new T[KOLUMNY];

		for (int j = 0; j < KOLUMNY; j++) {
			result[j] = matrix[wiersz - 1][j];
		}

		return result;
	}

	//+ создать вектор из столбца
	T* createVectorFromKols(int kol) {
		if (kol<0 || kol>KOLUMNY) {
			return nullptr;
		}
		T* result = new T[WIERSZY];

		for (int j = 0; j < WIERSZY; j++) {
			result[j] = matrix[j][kol - 1];
		}
		return result;
	}

	//+создание единичной матрицы через обратную матрицу
	CMatrix inversion()
	{
		CMatrix originMatrix;
		originMatrix = *this;
		if (KOLUMNY != WIERSZY)
		{
			return *this;
		}

		T temp;
		int N = WIERSZY;

		CMatrix matrixA(WIERSZY, KOLUMNY);

		for (int i = 0; i < N; i++)//заполнение единичной матрицы 
			for (int j = 0; j < N; j++)
			{
				matrixA[i][j] = 0.0;

				if (i == j)
					matrixA[i][j] = 1.0;
			}

		for (int k = 0; k < N; k++)
		{
			temp = matrix[k][k];

			for (int j = 0; j < N; j++)
			{
				matrix[k][j] /= temp;
				matrixA[k][j] /= temp;
			}

			for (int i = k + 1; i < N; i++)
			{
				temp = matrix[i][k];

				for (int j = 0; j < N; j++)
				{
					matrix[i][j] -= matrix[k][j] * temp;
					matrixA[i][j] -= matrixA[k][j] * temp;
				}
			}
		}

		for (int k = N - 1; k > 0; k--)
		{
			for (int i = k - 1; i >= 0; i--)
			{
				temp = matrix[i][k];

				for (int j = 0; j < N; j++)
				{
					matrix[i][j] -= matrix[k][j] * temp;
					matrixA[i][j] -= matrixA[k][j] * temp;
				}
			}
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				matrix[i][j] = matrixA[i][j];

		*this = originMatrix;

		matrixA.mPrint(); //печать обратной матрицы

		CMatrix res_matrix(WIERSZY, matrixA.KOLUMNY);

		for (int i = 0; i < WIERSZY; i++) {
			for (int j = 0; j < matrixA.KOLUMNY; j++) {
				res_matrix[i][j] = 0;
				for (int k = 0; k < KOLUMNY; k++)
				{
					res_matrix[i][j] += matrix[i][k] * matrixA[k][j];
				}
			}
		}
		return res_matrix;
	}



	


};
