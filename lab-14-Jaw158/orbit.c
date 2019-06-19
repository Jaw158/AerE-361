#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double u = 0.01215, e = 0.00001;

double xdd(double x, double y, double yd) {
  double a1, a2, a;
  a1 = (u-1)*(x-u)/pow((x-u)*(x-u)+y*y,1.5);
  a2 = u*(x+1-u)/pow((x+1-u)*(x+1-u)+y*y,1.5);
  a = a1-a2-2*yd+x;
  return a;
}

double ydd(double x, double y, double xd) {
  double b1, b2, b;
  b1 = (u-1)*y/pow((x-u)*(x-u)+y*y,1.5);
  b2 = u*y/pow((x+1-u)*(x+1-u)+y*y,1.5);
  b = b1-b2+2*xd-y;
  return b;
}

/*
double RK45(double x,double y,double xd,double yd) {
  
  return hmax, hmin;

  
  l1 = h*d
  k1 = h*f(s, v, d);
  l2 = h*(d+k1/4);
  k2 = h*f(s+h/4, v+h/4, d+l1/4);
  l3 = h*(d+3*k1/32+9*k2/32);
  k3 = h*f(s+3*h/8, v+3*h/8, d+3*l1/32+9*l2/32);
  l4 = h*(d+1932*k1/2197-7200*k2/2197+7296*k3/2197);
  k4 = h*f(s+12*h/13, v+12*h/13, d+1932*l1/2197-7200*l2/2197+7296*l3/2197);
  l5 = h*(d+439*k1/216-8*k2+3680*k3/513-845*k4/4104);
  k5 = h*f(s+h, v+h, d+439*l1/216-8*l2+3680*l3/513-845*l4/4104);
  
  k6 = h*f(s+h/s, v+h/2, dy-8*k1/27+2*k2-3544*k3/2565+1859*k4/4104-11*k5/40);
  d1 = d+25*k1/216+1408*k3/2565+2197*k4/4104-k5/5;
  d2 = d+16*k1/135+6656*k3/12825+28561*k4/56430-9*k5/50+2*k6/55;
  R = abs(d1-d2)/h;
  del = 0.84*pow(e/R,1/4);
  if (R <= e) {
    s = s
  
}
  */

//this function sanitzies float type inputs
int IsFloat(long double flt) {
  int count, code, first = 0, negative = 0, decimal = 0, mag = 0;
  count = getchar();
  //loop invariants: flt (the input being sanitized)
  while(1) {
    //checks for a digit, these are acceptable almost anywhere in a float
    if (count >= '0' && count <= '9') {
      count = getchar();
    }
    //checks is for a negative at the start
    else if (count == 45 && first == 0) {
      count = getchar();
      negative = 1;
    }
    //checks for one decimal not in the exponent
    else if (count == 46 && decimal == 0 && mag == 0) {
      count = getchar();
      decimal = 1;
    }
    //checks for one exponent (e or E)
    else if (mag == 0 && (count == 101 || count == 69)) {
      //the exponent cannot be first or first after a negative
      if ((first > 0 && negative == 0) || first > 1) {
	count = getchar();
	mag = 1;
	//the exponent must be followed by the sign of the power (+ or -)
        if (count == 45 || count == 43) {
          count = getchar();
	  //the power sign must be followed by a digit
	  if (count >= '0' && count <= '9') {
	    count = getchar();
	  }
	  //no digit following the power sign
	  else {
	    printf("ERROR: ENTER AN EXPONENT\n");
	    return 1;
	  }
        }
	//no power sign following exponent
        else {
	  printf("ERROR: SPECIFY POSITIVE OR NEGATIVE EXPONENT\n");
	  return 1;
        }
      }
      //number starts with exponent
      else {
	printf("ERROR: A BASE IS REQUIRED\n");
	return 1;
      }
    }
    //checks if end of input has been reached
    else if (count == 10) {
      return 0;
    }
    //invalid character entered in a float
    else {
      printf("ERROR: ENTER A NUMBER\n");
      return 1;
    }
    //tracks the position in the input, used for negative sign check
    first++;
  }
}

main() {
  double x, y, xd, yd, dV;
  int code, check = 0, length, t;
  char input[24];
  double kx1, kx2, kx3, kx4, kx5, kx6, ky1, ky2, ky3, ky4, ky5, ky6;
  double kxd1, kxd2, kxd3, kxd4, kxd5, kxd6, kyd1, kyd2, kyd3, kyd4, kyd5, kyd6;
  double x1, x2, y1, y2, xd1, xd2, yd1, yd2, R, R0, d, h, hmax, hmin;
  FILE *path;
  
  while (check == 0) {
    //intial spacecraft conditions
    x = 4670.46;
    y = 42164.1;
    xd = -9.238231;
    yd = 0;
    //intial loop end conditions
    h = 0.001;
    hmax = h;
    hmin = h;
    t = 0;
    //delta V
    printf("please enter a delta V: ");
    scanf("%lf",&dV);
    code = IsFloat(dV);
    if (code == 1) {
      return -1;
    }
    else if (dV == 0) {
    }
    else if (dV > 1.7e308 || dV < -1.7e308) {
      printf("ERROR: OVERFLOW\n");
      return -1;
    }
    else if (dV < 2.3e-308 && dV > -2.3e-308) {
      printf("ERROR: UNDERFLOW\n");
      return -1;
    }
    path = fopen("path.txt","w");
    fprintf(path, "%lf %lf\n", x, y);
    xd = xd-dV;
    x = x/384400;
    y = y/384400;
    xd = xd/1.0183028463;
    
    while (t < 100 && x > -379729.54/384400) {
      kxd1 = h*xdd(x,y,yd);
      kyd1 = h*ydd(x,y,xd);
      kx1 = h*xd;
      ky1 = h*yd;
      kxd2 = h*xdd(x+kx1/4,y+ky1/4,yd+kyd1/4);
      kyd2 = h*ydd(x+kx1/4,y+ky1/4,xd+kxd1/4);
      kx2 = h*(xd+kxd1/4);
      ky2 = h*(yd+kyd1/4);
      kxd3 = h*xdd(x+3*kx1/32+9*kx2/32,y+3*ky1/32+9*ky2/32,yd+3*kyd1/32+9*kyd2/32);
      kyd3 = h*ydd(x+3*kx1/32+9*kx2/32,y+3*ky1/32+9*ky2/32,xd+3*kxd1/32+9*kxd2/32);
      kx3 = h*(xd+3*kxd1/32+9*kxd2/32);
      ky3 = h*(yd+3*kyd1/32+9*kyd2/32);
      kxd4 = h*xdd(x+1932*kx1/2197-7200*kx2/2197+7296*kx3/2197,y+1932*ky1/2197-7200*ky2/2197+7296*ky3/2197,yd+1932*kyd1/2197-7200*kyd2/2197+7296*kyd3/2197);
      kyd4 = h*ydd(x+1932*kx1/2197-7200*kx2/2197+7296*kx3/2197,y+1932*ky1/2197-7200*ky2/2197+7296*ky3/2197,xd+1932*kxd1/2197-7200*kxd2/2197+7296*kxd3/2197);
      kx4 = h*(xd+1932*kxd1/2197-7200*kxd2/2197+7296*kxd3/2197);
      ky4 = h*(yd+1932*kyd1/2197-7200*kyd2/2197+7296*kyd3/2197);
      kxd5 = h*xdd(x+439*kx1/216-8*kx2+3680*kx3/513-845*kx4/4104,y+439*ky1/216-8*ky2+3680*ky3/513-845*ky4/4104,yd+439*kyd1/216-8*kyd2+3680*kyd3/513-845*kyd4/4104);
      kyd5 = h*ydd(x+439*kx1/216-8*kx2+3680*kx3/513-845*kx4/4104,y+439*ky1/216-8*ky2+3680*ky3/513-845*ky4/4104,xd+439*kxd1/216-8*kxd2+3680*kxd3/513-845*kxd4/4104);
      kx5 = h*(xd+439*kxd1/216-8*kxd2+3680*kxd3/513-845*kxd4/4104);
      ky5 = h*(yd+439*kyd1/216-8*kyd2+3680*kyd3/513-845*kyd4/4104);
      kxd6 = h*xdd(x-8*kx1/27+2*kx2-3544*kx3/2565+1859*kx4/4104-11*kx5/40,y-8*ky1/27+2*ky2-3544*ky3/2565+1859*ky4/4104-11*ky5/40,yd-8*kyd1/27+2*kyd2-3544*kyd3/2565+1859*kyd4/4104-11*kyd5/40);
      kyd6 = h*ydd(x-8*kx1/27+2*kx2-3544*kx3/2565+1859*kx4/4104-11*kx5/40,y-8*ky1/27+2*ky2-3544*ky3/2565+1859*ky4/4104-11*ky5/40,xd-8*kxd1/27+2*kxd2-3544*kxd3/2565+1859*kxd4/4104-11*kxd5/40);
      kx6 = h*(xd-8*kxd1/27+2*kxd2-3544*kxd3/2565+1859*kxd4/4104-11*kxd5/40);
      ky6 = h*(yd-8*kyd1/27+2*kyd2-3544*kyd3/2565+1859*kyd4/4104-11*kyd5/40);
      x1 = x+25*kx1/216+1408*kx3/2565+2197*kx4/4104-kx5/5;
      x2 = x+16*kx1/135+6656*kx3/12825+28561*kx4/56430-9*kx5/50+2*kx6/55;
      y1 = y+25*ky1/216+1408*ky3/2565+2197*ky4/4104-ky5/5;
      y2 = y+16*ky1/135+6656*ky3/12825+28561*ky4/56430-9*ky5/50+2*ky6/55;
      xd1 = xd+25*kxd1/216+1408*kxd3/2565+2197*kxd4/4104-kxd5/5;
      xd2 = xd+16*kxd1/135+6656*kxd3/12825+28561*kxd4/56430-9*kxd5/50+2*kxd6/55;
      yd1 = yd+25*kyd1/216+1408*kyd3/2565+2197*kyd4/4104-kyd5/5;
      yd2 = yd+16*kyd1/135+6656*kyd3/12825+28561*kyd4/56430-9*kyd5/50+2*kyd6/55;
      R = fabs(x1-x2)/h;
      //printf("%.8lf\n",R);
      R0 = fabs(y1-y2)/h;
      //printf("%.8lf\n",R0);
      if (R0 > R) {
        R = R0;
      }
      R0 = fabs(xd1-xd2)/h;
      //printf("%.8lf\n",R0);
      if (R0 > R) {
        R = R0;
      }
      R0 = fabs(yd1-yd2)/h;
      //printf("%.8lf\n",R0);
      if (R0 > R) {
        R = R0;
      }
      if (hmax < h) {
        hmax = h;
      }
      if (hmin > h) {
        hmin = h;
      }
      d = 0.84*pow(e/R,0.25);
      h = d*h;
      //printf("%lf %lf\n",d,e/R);
      //t++;
      if (R <= e) {
        x = x1;
        y = y1;
        xd = xd1;
        yd = yd1;
        //printf();
        //close = fabs(x1-379729.54/384400);
        t++;
        fprintf(path, "%lf %lf\n", x*384400, y*384400);
      }
      //printf("%d\n",t);
    }
    fclose(path);
    system("gnuplot path.gnuplot");
    printf("Are you happy with this trajectory? (y/n)\n");
    while (1) {
      scanf("%s",input);
      length = strlen(input);
      if (length > 24) {
	printf("please enter 'y' for yes or 'n' for no: ");
      }
      else if (strcmp(input, "y") == 0) {
        check = 1;
        break;
      }
      else if (strcmp(input, "n") == 0) {
        break;
      }
      else {
	printf("please enter 'y' for yes or 'n' for no: ");
      }
    }
  }
  system("gnuplot trajectory.gnuplot");
  printf("the maximum step size was: %lf\n",hmax);
  printf("the minimum step size was: %lf\n",hmin);
  printf("the number of evaluations was: %d\n",t);
}
  
