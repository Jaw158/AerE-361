#include <stdio.h>
#include <stdlib.h>

//this function sanitzies integer type inputs
int IsInt(long intgr) {
  int count, code, first = 0, negative = 0, decimal = 0, mag = 0;
  count = getchar();
  //loop invariants: intgr (the input being sanitized)
  while(1) {
    //checks for a digit, these are acceptable anywhere
    if (count >= '0' && count <= '9') {
      count = getchar();
    }
    //checks is for a negative at the start
    else if (count == 45 && first == 0) {
      count = getchar();
      negative = 1;
    }
    //checks for one decimal
    else if (count == 46 && decimal == 0 && mag == 0) {
      count = getchar();
      decimal = 1;
    }
    //checks if end of input has been reached
    else if (count == 10) {
      return 0;
    }
    //invalid character entered in an integer
    else {
      printf("ERROR: ENTER A NUMBER\n");
      return 1;
    }
    //tracks the position in the input, used for negative sign check
    first++;
  }
}

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

int main()
{
    // Declare Vairables
  int i,j,k,l,m,n, code;
    float **A, *x, a, a1;  //You'll need a few more variables, but only one matrix

    //defined matrix and x
    
    // Request System Order (Number of Equtions)
    printf("\nHow many equations: ");
    scanf("%d",&n);
    code = IsInt(n);
    if (code == 1) {
      return;
    }
    else if (n > 32767 || n < 0) {
      printf("ERROR: OVERFLOW\n");
    }

    // Allocate Dynamic Veriables
    // (psst... malloc is pretty good at this)
    A = malloc(sizeof(int *) * n+1); //allocated matrix
    for (i = 1; i <= n; i++) {
      A[i] = malloc(sizeof(int) * n);
    }
    x = malloc(sizeof(int) * n);
    
    // Request Augmented Matrix Values
    printf("\nEnter the elements of augmented matrix row-wise:\n");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=(n+1); j++)
        {
            printf(" A[%d][%d]:", i,j);
            scanf("%f",&A[i][j]); //indexed properly
	    code = IsFloat(A[i][j]);
	    if (code == 1) {
	      return;
	    }
	    else if (A[i][j] == 0) {
	    }
	    else if (A[i][j] > 3.4e38 || A[i][j] < -3.4e38) {
	      printf("ERROR: OVERFLOW\n");
	      return -1;
	    }
	    else if (A[i][j] < 1.2e-38 && A[i][j] > -1.2e-38) {
	      printf("ERROR: UNDERFLOW\n");
	      return -1;
	    }
        }
    }

    // Diagnolize the matrix
    for(j=1; j<=n; j++)
    {
        for(i=1; i<=n; i++)
        {
            if(i!=j)
            {
                // There is a useful intermediate value you can compute here
	      
	      if (A[j][j] == 0) {
		    for (l = j+1; l <= n; l++) {
		      if (A[l][j] != 0) {
			for (m = 1; m <= n+1; m++) {
			  a = A[j][m];
			  A[j][m] = A[l][m];
			  A[l][m] = a;
			}
		      }
			else if (l == n) {
			  printf("ERROR: TOO MANY EQUATIONS\n");
			  return -1;
			}
		      }
		    }
	      if (A[i][j] == 0) {
		continue;
	      }
	      a1 = A[i][j];
                for(k=1; k<=n+1; k++)
                {
                    // This is where the magic happens
		  
		  a = A[j][k]-(A[j][j]*A[i][k])/a1;
		  A[i][k] = a;
                }
            }
        }
	if (A[j][j] == 0) {
	  printf("ERROR: TOO FEW EQUATIONS\n");
	  return -1;
	}
    }


    printf("\nThe solution is:\n");
    for(i=1; i<=n; i++)
    {
        // One last math - compute the unknown from the diag and constant
      x[i] = A[i][n+1]/A[i][i];
        printf("\n x%d=%f\n",i,x[i]);
    }
    return(0);
}
