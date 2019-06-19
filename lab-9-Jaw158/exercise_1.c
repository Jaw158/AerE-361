#include <stdio.h>

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
  long double n, d, fplace, fbin, bin;
  long int i, iplace, ibin;
  int neg, a, b, r, code;
  
  printf("Enter a decimal number: ");
  scanf("%Lf",&n);
  code = IsFloat(n);
  if (n < 0) {
    n = n*-1;
    neg = 1;
  }
  i = (long int) n;
  d = n-i;
  if (code == 1) {
    return;
  }
  else if (i >= 1024) {
    printf("ERROR: OVERFLOW\n");
    return 1;
  }
  else if (d < 0.0009765625 && d != 0) {
    printf("ERROR: UNDERFLOW\n");
    return 1;
  }
  iplace = 1;
  ibin = 0;
  while (i > 0) {
    r = i%2;
    if (r == 1) {
      ibin = ibin+r*iplace;
    }
    i = i/2;
    iplace = iplace*10;
  }
  fplace = 1.0;
  fbin = 0;
  b = 0;
  while (d > 0 && b < 10) {
    b++;
    fplace = fplace/10;
    d = d*2;
    if (d >= 1) {
      fbin = fbin+fplace;
      d = d-1;
      a = b;
    }
  }
  bin = (long double) ibin+fbin;
  if (neg == 1) {
    bin = bin*-1;
  }
  printf("The binary number is: %.*Lf\n",a,bin);
}
