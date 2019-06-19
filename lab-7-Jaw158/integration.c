#include <stdio.h>

//This is a code of integration approximation functions, to be used with a separate main.c program
//integration functions must be passed a double returning function, and two double type integration bounds

//approximates integral via one midpoint-based rectangle
double midpoint(double (*f)(double),double a,double b) {
  double ans;
  ans = f((a+b)/2)*(b-a); //height times base
  return ans;
}

//approximates integral via simpson's 1/3 rule
double simpson_13(double (*f)(double),double a,double b) {
  double ans, simp;
  simp = f(a)+4*f((a+b/2))+f(b); //quadratic portion
  ans = (b-a)/6*simp; //horizontal portion
  return ans;
}

//approximates integral via simpson's 3/8 rule
double simpson_38(double (*f)(double),double a,double b) {
  double ans, simp;
  simp = f(a)+3*f((2*a+b)/3)+3*f((a+2*b)/3)+f(b); //cubic portion
  ans = (b-a)/8*simp; //horizontal portion
  return ans;
}

//approximates integral via guass quad method; requires 4th input of type integer
double gauss_quad(double (*f)(double),double a,double b,int n) {
  double ans, gauss, c, m;
  double t[11][11], w[11][11]; //predefined arrays store interessting parts
  int i;
  //the bounds of the integral are reset
  c = (a+b)/2;
  m = (b-a)/2;
  //matrices only store up to order 10, so this rejects anything not between orders 2 and 10
  if (n < 2 || n > 10) {
    printf("ERROR: ORDER MUST BE BETWEEN 2 AND 10\n");
    return -2; //main.c will think answer is -2, it isn't but I couldn't figure out how to supress an output from a separated function
  }
  //array of t points
  t[2][1]=0.57735027;
  t[2][2]=-0.57735027;
  t[3][2]=0.77459667;
  t[3][3]=-0.77459667;
  t[4][1]=0.33998104;
  t[4][2]=-0.33998104;
  t[4][3]=0.86113631;
  t[4][4]=-0.86113631;
  t[5][2]=0.53846931;
  t[5][3]=-0.53846931;
  t[5][4]=0.90617985;
  t[5][5]=-0.90617985;
  t[6][1]=0.23861918;
  t[6][2]=-0.23861918;
  t[6][3]=0.66120939;
  t[6][4]=-0.66120939;
  t[6][5]=0.93246951;
  t[6][6]=-0.93246951;
  t[7][2]=0.40584515;
  t[7][3]=-0.40584515;
  t[7][4]=0.74153119;
  t[7][5]=-0.74153119;
  t[7][6]=0.94910791;
  t[7][7]=-0.94910791;
  t[8][1]=0.18343464;
  t[8][2]=-0.18343464;
  t[8][3]=0.52553241;
  t[8][4]=-0.52553241;
  t[8][5]=0.79666648;
  t[8][6]=-0.79666648;
  t[8][7]=0.96028986;
  t[8][8]=-0.96028986;
  t[9][2]=0.32425342;
  t[9][3]=-0.32425342;
  t[9][4]=0.61337143;
  t[9][5]=-0.61337143;
  t[9][6]=0.83603111;
  t[9][7]=-0.83603111;
  t[9][8]=0.96816024;
  t[9][9]=-0.96816024;
  t[10][1]=0.14887434;
  t[10][2]=-0.14887434;
  t[10][3]=0.43339539;
  t[10][4]=-0.43339539;
  t[10][5]=0.67940957;
  t[10][6]=-0.67940957;
  t[10][7]=0.86506337;
  t[10][8]=-0.86506337;
  t[10][9]=0.97390653;
  t[10][10]=-0.97390653;
  //array of w weights
  w[2][1]=1;
  w[2][2]=1;
  w[3][1]=0.88888889;
  w[3][2]=0.55555555;
  w[3][3]=0.55555555;
  w[4][1]=0.65214515;
  w[4][2]=0.65214515;
  w[4][3]=0.34785485;
  w[4][4]=0.34785485;
  w[5][1]=0.56888889;
  w[5][2]=0.47862867;
  w[5][3]=0.47862867;
  w[5][4]=0.23692689;
  w[5][5]=0.23692689;
  w[6][1]=0.46791393;
  w[6][2]=0.46791393;
  w[6][3]=0.36076157;
  w[6][4]=0.36076157;
  w[6][5]=0.17132449;
  w[6][6]=0.17132449;
  w[7][1]=0.41795918;
  w[7][2]=0.38183005;
  w[7][3]=0.38183005;
  w[7][4]=0.27970539;
  w[7][5]=0.27970539;
  w[7][6]=0.12948497;
  w[7][7]=0.12948497;
  w[8][1]=0.36268378;
  w[8][2]=0.36268378;
  w[8][3]=0.31370665;
  w[8][4]=0.31370665;
  w[8][5]=0.22238103;
  w[8][6]=0.22238103;
  w[8][7]=0.10122854;
  w[8][8]=0.10122854;
  w[9][1]=0.33023936;
  w[9][2]=0.31234708;
  w[9][3]=0.31234708;
  w[9][4]=0.26061070;
  w[9][5]=0.26061070;
  w[9][6]=0.18064816;
  w[9][7]=0.18064816;
  w[9][8]=0.08127439;
  w[9][9]=0.08127439;
  w[10][1]=0.29552422;
  w[10][2]=0.29552422;
  w[10][3]=0.26926672;
  w[10][4]=0.26926672;
  w[10][5]=0.21908636;
  w[10][6]=0.21908636;
  w[10][7]=0.14945135;
  w[10][8]=0.14945135;
  w[10][9]=0.06667134;
  w[10][10]=0.06667134;
  //intial index for loop
  ans = 0;
  //the variables c and m are constant in the loop, additionally t and w are read-only
  for(i = 0; i <= n; ++i) {
    gauss = f(c+m*t[n][i]);
    ans = w[n][i]*gauss+ans;
  }
  return m*ans;
}