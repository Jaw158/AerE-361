#include <stdio.h>
#include <math.h>

//this function sanitzies float type inputs
int IsFloat(double  flt) {
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

//function for calculating factorial
double factorial(int n) {
  double alm = 1;
  //no loop invariants
  while (n > 0) {
    //calculates factorial
    alm *= n;
    n--;
  }
  return alm;
}

main() {
  int n, code;
  double x, flt, cnvrg, exp, sum;
  //inputs are asked for
  printf("Enter a real value for x: ");
  scanf("%lf",&x);
  //santizes possible inputs
  flt = x;
  code = IsFloat(flt);
  //checks for overflow error
  if (x > 3.4e+38) {
    printf("ERROR: UNACCEPTABLE x VALUE\n");
    return 1;
  }
  //acceptable input
  else if (code == 0) {
  }
  //filters out other surprises
  else {
    return 1;
  }
  //repeates process of asking for and sanitizing inputs
  printf("Enter the acceptable error: ");
  scanf("%lf",&cnvrg);
  flt = cnvrg;
  code = IsFloat(flt);
  //checks for underflow and overflow errors
  if (cnvrg < 2.3e-308 || cnvrg > 1.7e+308) {
    printf("ERROR: UNACCEPTABLE CONVERGENCE CRITERIA\n");
    return 1;
  }
  else if (code == 0) {
  }
  else {
    return 1;
  }
  n = 0;
  sum = 0;
  //loop invariants: x and cnvrg (the inputs)
  do {
    //calculates a single maclaurin series value, which is also the error
    exp = pow(x,n)/factorial(n);
    //adds all previous maclaurin series values
    sum = exp+sum;
    //prevents the loop from ending before convergence for criteria above 1
    if (cnvrg >= 1 && n < x) {
      exp = cnvrg+1;
    }
    n++;
  }
  //loop ends when convergence criteria exceeds the error
  while (fabsl(exp) > cnvrg);
    printf("\nThe estimated value of e^x is: %lf\n",sum);
    printf("The series required an order of %d to converge\n",n-1);
}
