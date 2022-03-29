#include "math.h"
#include "FFtypes.h"

double** criaMatriz(int l, int c);
double** multiplica(double** mat1, double** mat2);
double to180range(double angle);
double to360range(double angle);
double smallestAngleDiff(double target, double source);
double sign(double x);
double minimal(double a, double b, double c);
double dist(Point2f pt1, Point2f pt2);