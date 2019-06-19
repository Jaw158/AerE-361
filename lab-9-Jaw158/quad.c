#include <stdio.h>
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

main() {
  float a, b, c, discrim, absa, absb, absc, root1, root2;
  int code;
  //inputs coefficients and checks for validity
  printf("Enter the first coefficient of the quadratic equation: ");
  scanf("%f",&a);
  code = IsFloat(a);
  if (a < 0) {
    absa = a*-1;
  }
  else {
    absa = a;
  }
  if (code == 1) {
    return;
  }
  else if (absa > 3.4e38) {
    printf("ERROR: OVERFLOW\n");
    return 1;
  }
  else if (absa < 1.2e-38 && absa != 0) {
    printf("ERROR: UNDERFLOW\n");
    return 1;
  }
  else {
  }
  printf("Enter the second coefficient of the quadratic equation: ");
  scanf("%f",&b);
  code = IsFloat(b);
  if (b < 0) {
    absb = b*-1;
  }
  else {
    absb = b;
  }
  if (code == 1) {
    return;
  }
  else if (absb > 3.4e38) {
    printf("ERROR: OVERFLOW\n");
    return 1;
  }
  else if (absb < 1.2e-38 && absb != 0) {
    printf("ERROR: UNDERFLOW\n");
    return 1;
  }
  else {
  }
  printf("Enter the third coefficient of the quadratic equation: ");
  scanf("%f",&c);
  code = IsFloat(c);
  if (c < 0) {
    absc = c*-1;
  }
  else {
    absc = c;
  }
  if (code == 1) {
    return;
  }
  else if (absc > 3.4e38) {
    printf("ERROR: OVERFLOW\n");
    return 1;
  }
  else if (absc < 1.2e-38 && absc != 0) {
    printf("ERROR: UNDERFLOW\n");
    return 1;
  }
  else {
  }
  //determines largest coeffient
  if (absa >= absb && absa >= absc) {
    b = b/absa;
    c = c/absa;
    a = a/absa;
    discrim = b*b-4*c;
  }
  else if (absb >= absa && absb >= absc) {
    c = c/absb;
    a = a/absb;
    b = b/absb;
    if (absa >= absc) {
      discrim = 1-(4*a)*c;
    }
    else {
      discrim = 1-(4*c)*a;
    }
  }
  else {
    a = a/absc;
    b = b/absc;
    c = c/absc;
    discrim = b*b-4*a;
  }
  //finds roots, different proccess if roots are real or imaginary
  if (discrim < 0) {
    discrim = sqrt(discrim*-1);
    b = b*-1;
    root1 = b/(2*a);
    root2 = discrim/(2*a);
    printf("\nThe roots are %f+i%f and %f-i%f\n",root1,root2,root1,root2);
  }
  else {
    discrim = sqrt(discrim);
    if (b < 0) {
      b = b*-1;
      root1 = (b+discrim)/(2*a);
      root2 = (2*c)/(b+discrim);
    }
    else {
      b = b*-1;
      root1 = (b-discrim)/(2*a);
      root2 = (2*c)/(b-discrim);
    }
    printf("\nThe roots are %f and %f\n",root1,root2);
  }
}
