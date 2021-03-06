// numerki_projekt2.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<math.h>
#include <ctime>

double** allocate_matrix(const int size_n)
{
	double **ptr;
	ptr = new double*[size_n];
	for (int i = 0; i < size_n; i++)
	{
		ptr[i] = new double[size_n];
	}
	return ptr;
}

void free_matrix(double **ptr, const int size_n)
{
	for (int i = 0; i < size_n; i++)
	{
		delete[] ptr[i];
	}
	delete[] ptr;
}

void coppy_matrix(double **src, double **dst, const int size_n)
{
	for (int i = 0; i<size_n; i++)
	{
		for (int j = 0; j<size_n; j++)
		{
			dst[i][j] = src[i][j];
		}
	}
}

void ones_matrix(double **matrix, const int size_n)
{
	for (int i = 0; i<size_n; i++)
	{
		for (int j = 0; j<size_n; j++)
		{
			if (j == i) matrix[i][j] = 1;
			else matrix[i][j] = 0;
		}
	}
}

void init_vector_b(double *vect_b, const int size_n) {
	for (int i = 0; i < size_n; i++) {
		vect_b[i] = sin(i*(5.0 + 1.0));
	}
}

void init_vector_x(double *vectX, const int size_n) {
	for (int i = 0; i < size_n; i++) {
		vectX[i] = 1.0;
	}
}

void init_vector_x1(double *vectX, double *vectX1, const int size_n) {
	for (int i = 0; i < size_n; i++) {
		vectX1[i] = vectX[i];
	}
}

void update_vector_x(double *vectX, double *vectX1, const int size_n) {
	for (int i = 0; i < size_n; i++) {
		vectX[i] = vectX1[i];
	}
}

void init_vector_res(double *vect_res, const int size_n) {
	for (int i = 0; i < size_n; i++) {
		vect_res[i] = 1.0;
	}
}

void update_vector_res(double **matrixA, double *vect_b, double *vect_res, double *vectX, const int size_n) {
	double tmp;
	for (int i = 0; i < size_n; i++) {
		tmp = 0.0;
		for (int j = 0; j < size_n; j++)
		{
			tmp += matrixA[i][j] * vectX[j];
		}
		vect_res[i] = tmp - vect_b[i];
	}
}

void init_matrix_a(double **matrixA, const int size_n, double a1, double a2, double a3)
{

	for (int i = 0; i< size_n; i++)
	{
		for (int j = 0; j<size_n; j++)
		{
			matrixA[i][j] = 0;
		}
	}

	matrixA[0][0] = a1;
	matrixA[0][1] = a2;
	matrixA[0][2] = a3;

	matrixA[1][0] = a2;
	matrixA[1][1] = a1;
	matrixA[1][2] = a2;
	matrixA[1][3] = a3;

	for (int i = 2; i < size_n - 2; ++i)
	{
		matrixA[i][i - 2] = a3;
		matrixA[i][i - 1] = a2;
		matrixA[i][i] = a1;
		matrixA[i][i + 1] = a2;
		matrixA[i][i + 2] = a3;
	}

	matrixA[size_n - 2][size_n - 4] = a3;
	matrixA[size_n - 2][size_n - 3] = a2;
	matrixA[size_n - 2][size_n - 2] = a1;
	matrixA[size_n - 2][size_n - 1] = a2;

	matrixA[size_n - 1][size_n - 3] = a3;
	matrixA[size_n - 1][size_n - 2] = a2;
	matrixA[size_n - 1][size_n - 1] = a1;
}

void print_matrix(double **matrixA, const int size_n)
{
	for (int i = 0; i< size_n; i++)
	{
		for (int j = 0; j < size_n; j++)
		{
			std::cout.width(10);
			std::cout << matrixA[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void print_vector(double *vect, const int size_n) {

	for (int i = 0; i < size_n; i++)
	{
		std::cout.width(10);
		std::cout << vect[i] << " ";
	}
	std::cout << std::endl;
}

double licz_norme(double *vect, const int size_n)
{
	double suma = 0.0;
	for (int i = 0; i<size_n; i++)
	{
		suma += vect[i] * vect[i];
		//suma += pow(vect[i], 2.0);
	}
	return sqrt(suma);
}

void jacobi(double **matrix_a, double *vect_b, double *vect_res, double *vect_x, double *vect_x1, const int size_n)
{
	init_vector_x(vect_x, size_n);
	init_vector_x1(vect_x, vect_x1, size_n);
	init_vector_res(vect_res, size_n);
	double tmp;
	int k = 0;
	std::cout << "############ Jacobi ################ " << std::endl;
	update_vector_res(matrix_a, vect_b, vect_res, vect_x, size_n);
	double norma = licz_norme(vect_res, size_n);
	std::cout << "Norma residuum: " << norma << std::endl;
	const double dokladnosc = 10e-9;
	clock_t start = clock();
	for (; norma > dokladnosc; k++)
	{
		for (int i = 0; i < size_n; i++)
		{
			//tmp = 0;
			tmp = vect_b[i];
			for (int j = 0; j < i; j++)
			{
				tmp -= matrix_a[i][j] * vect_x[j];
			}
			for (int j = i + 1; j < size_n; j++)
			{
				tmp -= matrix_a[i][j] * vect_x[j];
			}

			tmp /= matrix_a[i][i];
			vect_x1[i] = tmp;
		}
		update_vector_x(vect_x, vect_x1, size_n);
		update_vector_res(matrix_a, vect_b, vect_res, vect_x, size_n);
		//printVectorRes();
		norma = licz_norme(vect_res, size_n);
		//print_vector(vect_x, size_n);
		std::cout << "Norma residuum: " << norma << std::endl;
		//if (k >= 50) break;

	}
	std::cout << "Obiegow: " << k << std::endl << "Dokladnosc: " << norma << std::endl << "Czas trwania: " << clock() - start << std::endl;

}

void gauss_seidl(double **matrixA, double *vect_b, double *vect_res, double *vect_x, double *vect_x1, const int size_n)
{
	init_vector_x(vect_x, size_n);
	init_vector_x1(vect_x, vect_x1, size_n);
	init_vector_res(vect_res, size_n);
	double tmp;
	int k = 0;
	std::cout << "############ Gaus Seidel ################ " << std::endl;
	update_vector_res(matrixA, vect_b, vect_res, vect_x, size_n);
	double norma = licz_norme(vect_res, size_n);
	std::cout << "Norma residuum: " << norma << std::endl;
	const double dokladnosc = 10e-9;
	clock_t start = clock();
	for (; norma > dokladnosc; k++)
	{
		for (int i = 0; i < size_n; i++)
		{
			//tmp = 0;
			tmp = vect_b[i];
			for (int j = 0; j < i; j++)
			{
				tmp -= matrixA[i][j] * vect_x[j];
			}
			for (int j = i + 1; j < size_n; j++)
			{
				tmp -= matrixA[i][j] * vect_x[j];
			}

			tmp /= matrixA[i][i];
			vect_x1[i] = tmp;
			update_vector_x(vect_x, vect_x1, size_n);
		}
		//update_vector_x(vect_x, vect_x1, size_n);
		update_vector_res(matrixA, vect_b, vect_res, vect_x, size_n);
		//printVectorRes();
		norma = licz_norme(vect_res, size_n);
		//print_vector(vect_x, size_n);
		std::cout << "Norma residuum: " << norma << std::endl;
		//if (k >= 50) break;
	}
	std::cout << "Obiegow: " << k << std::endl << "Dokladnosc: " << norma << std::endl << "Czas trwania: " << clock() - start << std::endl;

}

void lu(double **matrix_a, double **matrix_l, double **matrix_u, double *vect_b, double *vect_x, double *vect_res, const int size_n)
{
	std::cout << std::endl << "############ LU factorization ################ " << std::endl;
	clock_t start = clock();
	double *vect_y = new double[size_n];
	init_vector_x(vect_x, size_n);
	init_vector_res(vect_res, size_n);
	coppy_matrix(matrix_a, matrix_u, size_n);
	ones_matrix(matrix_l, size_n);
	for (int k = 0; k<size_n-1 ; k++)
	{
		for (int j = k+1; j<size_n; j++)
		{
			matrix_l[j][k] = matrix_u[j][k] / matrix_u[k][k];
			for (int m = k; m < size_n; m++) {
				matrix_u[j][m] -= matrix_l[j][k] * matrix_u[k][m];
			}			
		}
	}

	/*
	std::cout << "Macierz L" << std::endl;
	print_matrix(matrix_l, size_n);	
	std::cout << "Macierz U" << std::endl;
	print_matrix(matrix_u, size_n);
	*/
	//podstawianie wprzód
	for (int i = 0; i < size_n; i++)
	{
		double tmp = vect_b[i];
		for (int j = 0; j<i; j++)
		{
			tmp -= matrix_l[i][j] * vect_y[j];
		}		
		vect_y[i] = tmp;
	}
	//print_vector(vect_y, size_n);

	//podstawianie wstecz
	for (int i = 1; i <= size_n; i++)
	{
		double tmp = vect_y[size_n-i];

		for (int j = 1; j < i; j++)
		{
			tmp -= matrix_u[size_n-i][size_n-j] * vect_x[size_n-j];
		}
		tmp /= matrix_u[size_n-i][size_n-i];
		vect_x[size_n-i] = tmp;
	}
	
	std::cout << "\nCzas trwania: " << clock() - start << std::endl;	
	update_vector_res(matrix_a, vect_b, vect_res, vect_x, size_n);
	std::cout << "Norma wektora res: " << licz_norme(vect_res, size_n) << std::endl;
}

int main() {
	//wymagania zadania
	// c = 9 
	// d = 6 
	// e = 4 
	// f = 5 
	// size_n = 9cd
	//const int size_n = 996;
	//const int size_n = 10;
	const int size_n = 16000;
	//a1 = 5+e = 5+4
	const double a1 = 5.0 + 4.0;
	const double a2 = -1.0, a3 = -1.0;

	double **matrix_a = allocate_matrix(size_n);
	double *vect_b = new double[size_n];
	double *vect_res = new double[size_n];
	double *vect_x = new double[size_n];
	double *vect_x1 = new double[size_n];

	init_vector_b(vect_b, size_n);
	init_matrix_a(matrix_a, size_n, a1, a2, a3);

	//print_matrix(matrix_a, size_n);
	//print_vector(vect_res, size_n);
	//print_vector(vect_b, size_n);
	//print_vector(vect_x, size_n);

	//std::cout << "Norma: " << licz_norme(vect_res, size_n) << std::endl;
	jacobi(matrix_a, vect_b, vect_res, vect_x, vect_x1, size_n);
	//std::cout << "Rozwiazanie: " << std::endl;
	//print_vector(vect_x, size_n);

	std::cout << std::endl;
	// ---------------- podpunkt B (GS) -----------------

	gauss_seidl(matrix_a, vect_b, vect_res, vect_x, vect_x1, size_n);
	//std::cout << "Rozwiazanie: " << std::endl;
	//print_vector(vect_x, size_n);

	/*
	// ---------------- Zadanie C -----------------
	std::cout << std::endl;
	std::cout << "Zadanie C"<<std::endl;

	double **matrix_m =	allocate_matrix(size_n);
	init_matrix_a(matrix_m, size_n, 3, -1, -1);
	*/
	/*	
	jacobi(matrix_m, vect_b, vect_res, vect_x, vect_x1, size_n);	
	gauss_seidl(matrix_m, vect_b, vect_res, vect_x, vect_x1, size_n);
	*/
	// ---------------- Zadanie D -----------------
	/*
	std::cout << std::endl;
	std::cout << "Zadanie D" << std::endl;
	//print_matrix(matrix_a, size_n);
	double **matrix_L = allocate_matrix(size_n);
	double **matrix_U = allocate_matrix(size_n);
	lu(matrix_m, matrix_L, matrix_U, vect_b, vect_x, vect_res, size_n);	
	//std::cout << "Wektor wynikowy: " << std::endl;
	//print_vector(vect_x, size_n);
	*/
	free_matrix(matrix_a, size_n);
	delete vect_x;
	delete vect_b;
	delete vect_res;
	delete vect_x1;
	return 0;
}