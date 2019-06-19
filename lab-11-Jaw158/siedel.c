#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int IsFile(char check[]) {
  int loop, pos = -1;
  for (loop = 0; loop < strlen(check); ++loop) {
    if (loop == pos) {
      if (check[pos] == 'c') {
	if (check[pos+1] == 's') {
	  if (check[pos+2] == 'v') {
	    if (strlen(check) == pos+3) {
	      return 0;
	    }
	    else {
	      printf("ERROR: NOT A CSV FILE\n");
	    }
	  }
	  else {
	    printf("ERROR: NOT A CSV FILE\n");
	    return;
	  }
	}
	else {
	  printf("ERROR: NOT A CSV FILE\n");
	  return;
	}
      }
      else {
	printf("ERROR: NOT A CSV FILE\n");
	return;
      }
    }
    else if (check[loop] == '.') {
      pos = loop+1;
    }
  }
}

int FloatChar(char check[42]) {
  int loop, dec = 0;
  for (loop = 0; loop < strlen(check); ++loop) {
    if (check[loop] == 10) {
    }
    else if (check[loop] >= '0' && check[loop] <= '9') {
    }
    else if (check[loop] == '-' && loop != 1) {
      printf("ERROR: NEGATIVES MUST BE AT START");
      return -1;
    }
    else if (check[loop] == '.' && dec == 0) {
      dec = 1;
    }
    else {
      printf("ERROR: INVALID INPUT\n");
      return -1;
    }
  }
  if (loop == strlen(check)) {
    return 0;
  }
}

int IntChar(char check[42]) {
  int loop, dec = 0;
  for (loop = 0; loop < strlen(check); ++loop) {
    if (check[loop] == 10) {
    }
    else if (check[loop] >= '0' && check[loop] <= '9') {
    }
    else if (check[loop] == '-' && loop != 1) {
      printf("ERROR: NEGATIVES MUST BE AT START");
      return -1;
    }
    else {
      printf("ERROR: INVALID INPUT\n");
      return -1;
    }
  }
  if (loop == strlen(check)) {
    return 0;
  }
}

main(int argc, char* argv[]) {
  FILE *csv, *ans;
  char buff[1024];
  char *value, *line;
  int flag = 0, n = 0, i, j, k, suma, sumb, code;
  int iter = 100;
  double tole = 1e-4;
  double **mat, *x0, *x;

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i],"-i") == 0) {
      i = i+1;
      if (i >= argc) {
	printf("ERROR: EXPECTED NUMBER AFTER FLAG\n");
	return -1;
      }
      code = IntChar(argv[i]);
      iter = atoi(argv[i]);
      if (code == 1) {
	return;
      }
      else if (iter > 32767 || iter < 0) {
	printf("ERROR: OVERFLOW\n");
	return -1;
      }
      else {
	flag = flag+2;
      }
    }
    else if (strcmp(argv[i],"-e") == 0) {
      i = i+1;
      if (i >= argc) {
	printf("ERROR: EXPECTED NUMBER AFTER FLAG\n");
	return -1;
      }
      code = FloatChar(argv[i]);
      tole = atof(argv[i]);
      if (code == 1) {
	return;
      }
      else if (tole > 1.7e308 || tole < -1.7e308) {
	printf("ERROR: OVERFLOW\n");
	return -1;
      }
      else if (tole < 2.3e-308 && tole < -2.3e-308 && tole != 0) {
	printf("ERROR: UNDERFLOW\n");
      }
      else {
	flag = flag+2;
      }
    }
    else if (strcmp(argv[i],"-h") == 0) {
      printf("input either a csv file or nothing; if nothing the computer will ask for coefficients\n");
      printf("use -i to change the number of iterations, -e to change the tolerance, -h for help\n");
    }
  }
		 
  if (argc-flag == 1) {
    printf("Enter the number of equations: ");
    scanf("%d",&n);
    code = IsInt(n);
    if (code == 1) {
      return;
    }
    else if (n > 32767 || n < 0) {
      printf("ERROR: OVERFLOW\n");
      return -1;
    }
    mat = malloc(sizeof(int *) * n);
    for (i = 0; i < n; ++i) {
      mat[i] = malloc(sizeof(int) * n+1);
    }
    for (i = 0; i < n; ++i) {
      printf("\n");
      for (j = 0; j < n; ++j) {
	printf("Enter coefficient %d of equation %d: ",j+1,i+1);
	scanf("%lf",&mat[i][j]);
	code = IsFloat(mat[i][j]);
	if (code == 1) {
	  return;
	}
	else if (mat[i][j] == 0) {
	}
	else if (mat[i][j] > 3.4e38 || mat[i][j] < -3.4e38) {
	  printf("ERROR: OVERFLOW\n");
	  return -1;
	}
	else if (mat[i][j] < 1.2e-38 && mat[i][j] > -1.2e-38) {
	  printf("ERROR: UNDERFLOW\n");
	  return -1;
	}
      }
      printf("Enter the solution of equation %d: ",i+1);
      scanf("%lf",&mat[i][n]);
      code = IsFloat(mat[i][n]);
      if (code == 1) {
	return;
      }
      else if (mat[i][n] == 0) {
      }
      else if (mat[i][n] > 3.4e38 || mat[i][n] < -3.4e38) {
	printf("ERROR: OVERFLOW\n");
	return 1;
      }
      else if (mat[i][n] < 1.2e-38 && mat[i][n] > -1.2e-38) {
	printf("ERROR: UNDERFLOW\n");
	return -1;
      }
    }
  }
  else if (argc-flag == 2) {
    code = IsFile(argv[1]);
    if (code != 0) {
      return -1;
    }
    csv = fopen(argv[1],"r");
    if (csv == NULL) {
      printf("ERROR: FILE NOT READABLE\n");
      return -1;
    }
    while ((line = fgets(buff, sizeof(buff), csv)) != NULL) {
      value = strtok(line,"\n");
      n++;
    }
    fseek(csv, 0, SEEK_SET);
    mat = malloc(sizeof(int *) * n);
    for (i = 0; i < n; ++i) {
      mat[i] = malloc(sizeof(int) * n+1);
    }
    i = 0;
    while ((line = fgets(buff, sizeof(buff), csv)) != NULL) {
      j = 0;
      value = strtok(line,",");
      while (value != NULL) {
	code = FloatChar(value);
	if (code != 0) {
	  return;
	}
	else if (atof(value) == 0) {
	}
	else if (atof(value) > 3.4e38 || atof(value) < -3.4e38) {
	  printf("ERROR: OVERFLOW\n");
	  return -1;
	}
	else if (atof(value) < 1.2e-38 && atof(value) > -1.2e-38) {
	  printf("ERROR: UNDERFLOW\n");
	  return -1;
	}
	mat[i][j++] = atof(value);
	value = strtok(NULL,",");
      }
      if (j != n+1) {
	printf("ERROR: IMPROPERLY FORMED MATRIX\n");
      }
      ++i;
    }
    fclose(csv);
  }
  else {
    printf("ERROR: TOO MANY ARGUMENTS\n");
    return -1;
  }
  x0 = malloc(sizeof(int) * n);
  x = malloc(sizeof(int) * n);
  for (i = 0; i < n; i++) {
    x0[i] = 0;
  }
  //math portion
  for (k = 0; k < iter; k++) {
    for (i = 0; i < n; i++) {
      suma = 0;
      sumb = 0;
      for (j = 0; j < i; j++) {
	suma = mat[i][j]*x[j]+suma;
      }
      for (j = i+1; j < n; j++) {
	sumb = mat[i][j]*x0[j]+sumb;
      }
      x[i] = (mat[i][n]-(suma+sumb))/mat[i][i];
    }
    j = 0;
    for (i = 0; i < n; ++i) {
      if (x[i]-x0[i] < tole && x[i]-x0[i] > -tole) {
	j++;
      }
    }
    if (j == n) {
      break;
    }
    for (i = 0; i < n; i++) {
      x0[i] = x[i];
    }
  }
  if (j != n) {
    printf("\nSystem of equations has not converged within maximum number of iterations, system may be divergent\n");
  }
  //output
  if (argc-flag == 1) {
    printf("\n");
    for (i = 0; i < n; i++) {
      printf("x%d = %lf\n",i+1,x[i]);
    }
  }
  else if (argc-flag == 2) {
    ans = fopen("ans.csv","w");
    for (i = 0; i < n; i++) {
      fprintf(ans, "%lf", x[i]);
      if (i != n-1) {
	fprintf(ans, "\n");
      }
    }
    fclose(ans);
  }
}
