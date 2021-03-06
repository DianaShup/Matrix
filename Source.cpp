#include <iostream>
#include "CMatrix.h"
template <typename T>
CMatrix<T> createMatrix(int WIERSZY, int KOLUMNY) {
	CMatrix<T> matrix(WIERSZY, KOLUMNY);
	for (int i = 0; i < WIERSZY; i++) {
		for (int j = 0; j < KOLUMNY; j++) {
			matrix[i][j] = rand()%10;
		}
	}
	return matrix;

}

int main() {

	CMatrix<double> matrix(3, 3);
	matrix[0][0] = 12;
	matrix[0][1] = 14;
	matrix[0][2] = 15;
	matrix[1][0] = 1;
	matrix[1][1] = 10;
	matrix[1][2] = 18;
	matrix[2][0] = 2;
	matrix[2][1] = 3;
	matrix[2][2] = 7;


	CMatrix<double> matrix2(2, 3);
	matrix2[0][0] = 2;
	matrix2[0][1] = 23;
	matrix2[0][2] = 1;
	matrix2[1][0] = 18;
	matrix2[1][1] = 2;
	matrix2[1][2] = 3;

	CMatrix<double> matrix3(3, 3);
	matrix3[0][0] = 1;
	matrix3[0][1] = 1;
	matrix3[0][2] = 12;
	matrix3[1][0] = 10;
	matrix3[1][1] = 11;
	matrix3[1][2] = 14;
	matrix3[2][0] = 21;
	matrix3[2][1] = 3;
	matrix3[2][2] = 17;

	CMatrix<double> matrix4(3, 3);

	//realizacja
	matrix4 = matrix + matrix3;
	std::cout << "Matrix A: " << std::endl;
	matrix.mPrint();
	std::cout << "Matrix B: " << std::endl;
	matrix3.mPrint();
	std::cout << "Suma: " << std::endl;
	matrix4.mPrint();
	matrix4 = matrix - matrix3;
	std::cout << "Roznica: " << std::endl;
	matrix4.mPrint();

	matrix.readFromFile("f:\\mat_float_double_example.txt");
	std::cout << "Macierz z pliku: " << std::endl;
	matrix.mPrint();

	matrix4 = matrix2 * 4;
	std::cout << " " << std::endl;
	std::cout << "MatrixA: " << std::endl;
	matrix2.mPrint();
	std::cout << "Mnozenie macierzy przez liczbe: " << std::endl;
	matrix4.mPrint();

	CMatrix<double>matrix5;
	std::cout << "Transponowanie macierzy: " << std::endl;
	matrix5 = matrix2.getmTransponate();
	matrix5.mPrint();

	CMatrix<double> matrix6(3, 3);
	matrix6[0][0] = 7;
	matrix6[0][1] = 9;
	matrix6[0][2] = 19;
	matrix6[1][0] = 10;
	matrix6[1][1] = 11;
	matrix6[1][2] = 5;
	matrix6[2][0] = 21;
	matrix6[2][1] = 3;
	matrix6[2][2] = 17;

	double vector[] = { 2,3,3 };
	double *rez = matrix6.multiplyVector(vector, 3);
	std::cout << "Mnozenie przez vector" << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << rez[i] << std::endl;
	}
	std::cout << "MatrixA: " << std::endl;
	matrix6.mPrint();
	std::cout << "MatrixB: " << std::endl;
	matrix3.mPrint();

	matrix4 = matrix6.multiplyMatrix(matrix3);
	std::cout << "MatrixA*MatrixB: " << std::endl;
	matrix4.mPrint();

	std::cout << " " << std::endl;

	std::cout << "Wektor z kolumny: " << std::endl;
	double*rez2 = matrix4.createVectorFromKols(1);
	for (int i = 0; i < 3; i++) {
		std::cout << rez2[i] << std::endl;
	}
	std::cout << "Wektor z wiersza: " << std::endl;
	rez2 = matrix4.createVectorFromRow(2);
	for (int i = 0; i < 3; i++) {
		std::cout << rez2[i] << std::endl;
	}


	CMatrix <double> matrix7;
	matrix7 = createMatrix<double>(3, 3);
	
	matrix7.mPrint();

	CMatrix<double>matrix8(3, 3);
    matrix7 *= matrix6;
	std::cout << " " << std::endl;
	matrix7.mPrint();



	//matrix.readFromFile("f:\\mat_float_double_example.txt");
	//matrix.mPrint();
	//matrix3 = matrix.inversion();
	//matrix3.mPrint();
	system("pause");
	return 0;
}