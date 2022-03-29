#include "include/ffMath.h"

// Retorna uma matruz com l linhas e c colunas
double** criaMatriz(int l, int c) {
	double** mat = new double* [l];
	for (int i = 0; i < l; i++) {
		mat[i] = new double[c];
	}
	return mat;
}

// Retorna a multiplica��o das matrizes mat1 e mat2
double** multiplica(double** mat1, double** mat2) {
	double soma;
	double** matR = criaMatriz(3, 1);
	for (int i = 0; i < 3; i++) {
		soma = 0;
		for (int j = 0; j < 3; j++) {
			soma += mat1[i][j] * mat2[j][0];
		}
		matR[i][0] = soma;
	}
	return matR;
}

// Pega qualquer �ngulo e retorna ele no intervalo de -pi a pi
double to180range(double angle) {
	angle = fmod(angle, 2 * M_PI);
	if (angle < -M_PI) {
		angle = angle + 2 * M_PI;
	}
	else if (angle > M_PI) {
		angle = angle - 2 * M_PI;
	}
	return angle;
}

// Pega qualquer angulo e retorna ele no intervalo de 0 a 2pi
double to360range(double angle) {
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0) {
		angle = angle + 2 * M_PI;
	}
	else if (angle > 2 * M_PI) {
		angle = angle - 2 * M_PI;
	}
	return angle;
}

// Retorna a menor diferen�a entre 2 �ngulos
double smallestAngleDiff(double target, double source) {
	double a;
	a = fmod(target + 2 * M_PI, 2 * M_PI) - fmod(source + 2 * M_PI, 2 * M_PI);

	if (a > M_PI) {
		a = a - 2 * M_PI;
	}
	else if (a < -M_PI) {
		a = a + 2 * M_PI;
	}
	return a;
}

// Retorna -1 para n�meros negativos e +1 para n�meros positivos
double sign(double x) {
	if (x == 0) {
		return 1;
	}
	return (x / abs(x));
}

// Retorna o menor entre os 3 par�metros
double minimal(double a, double b, double c) {
	double menor = a;
	if (b < menor) {
		menor = b;
	} if (c < menor) {
		menor = c;
	}
	return menor;
}

// Retorna a distancia entre os pontos pt1 e pt2
double dist(Point2f pt1, Point2f pt2) {
	return sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y));
}