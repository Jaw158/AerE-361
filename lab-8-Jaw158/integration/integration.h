#include <stdio.h>

struct integral {
  double (*integrand)(double);
  double low, high;
};

double midpoint(struct integral I);
double simpson_13(struct integral I);
double simpson_38(struct integral I);
double gauss_quad(struct integral I,int);
