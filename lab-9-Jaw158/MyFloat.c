#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

main () {
  int expo, mant, sign, *exponent, *mantissa;
  long int bexpo;
  int loop, e = 0, normal = 1, code, c;
  float n;
  long double max, min, swtch;
  
  printf("Enter an integer between 1 and 30 for the number of exponent bits: ");
  scanf("%d",&expo);
  //filter decimal exponent values
  c = getchar();
  while (c != 10) {
    if (c >= '0' && c <= '9') {
      c = getchar();
    }
    else {
      printf("ERROR: NOT AN INTEGER\n");
      return 1;
    }
  }
  if (0 < expo && expo < 31) {
    mant = 31-expo;
    printf("The significand will use %d bits\n",mant);
  }
  else {
    printf("ERROR: INVALID INPUT FOR EXPONENT BITS\n");
    return 1;
  }
  exponent = malloc(sizeof(int) * expo);
  mantissa = malloc(sizeof(int) * mant);
  bexpo = pow(2.0,expo-1)-1;
  printf("Enter a signed decimal number: ");
  scanf("%f",&n);
  //sanitize as float
  code = IsFloat(n);
  //check for overflow/underflow based on exponent/significand
  max = pow(2.0,bexpo);
  min = pow(2.0,1-bexpo-mant);
  swtch = pow(2.0,1-bexpo);
  if (n < 0) {
    n = n*-1;
    sign = 1;
  }
  if (code == 1) {
    return;
  }
  else if (n > max) {
    printf("ERROR: OVERFLOW\n");
    return 1;
  }
  else if (n == 0) {
  }
  else if (n < min) {
    printf("ERROR: UNDERFLOW\n");
    return 1;
  }
  else if (n < max && n >= swtch) {
    //determine size of exponent through multiplication or division by 2
    while (n < 1) {
      n = n*2;
      --e;
    }
    while (n >= 2) {
      n = n/2;
      ++e;
    }
    n = n-1;
    e = e+bexpo;
    for (loop = 0; loop < expo; ++loop) {
      exponent[expo-loop-1] = e%2;
      e = e/2;
    }
    for (loop = 0; loop < mant; ++loop) {
      n = n*2;
      if (n >= 1) {
        mantissa[loop] = 1;
        n = n-1;
      }
    }
  }
  else if (n < swtch && n > min) {
    for (loop = 0; loop < bexpo-1; ++loop) {
      n = n*2;
    }
    for (loop = 0; loop < mant; ++loop) {
      if (n >= 1) {
        mantissa[loop] = 1;
        n = n-1;
      }
      n = n*2;
    }
  }
  else {
    printf("ERROR: UNKNOWN\n");
    return 1;
  }
  printf("The floating point binary number is: %d ",sign);
  for (loop = 0; loop < expo; ++loop) {
    printf("%d",exponent[loop]);
  }
  printf(" ");
  for (loop = 0; loop < mant; ++loop) {
    printf("%d",mantissa[loop]);
  }
  printf("\n");
}
