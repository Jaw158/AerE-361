#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

main(int argc, char* argv[]) {
  FILE *fone, *ftwo, *ans; 
   char buff[1024];
   char *value, *line;
   int loop, code = -1;
   int i = 0, j = 0, k, m1 = 0, m2 = 0, n1 = 0, n2 = 0;
   float sum = 0;
   float **mone, **mtwo, **prod;

   if (argc != 3) {
     printf("ERROR: TWO FILE NAMES REQUIRED\n");
     return -1;
   }
   code = IsFile(argv[1]);
   if (code != 0) {
     return -1;
   }
   code = IsFile(argv[2]);
   if (code != 0) {
     return -1;
   }
   //open files
   fone = fopen(argv[1],"r");
   ftwo = fopen(argv[2],"r");
   //check files can be read
   if (fone == NULL) {
     printf("ERROR: FILE NOT READABLE\n");
     return -1;
   }
   if (ftwo == NULL) {
     printf("ERROR: FILE NOT READABLE\n");
     return -1;
   }
   //check row length
   line = fgets(buff,sizeof(buff),fone);
   value = strtok(line,",");
   while(value != NULL) {
     n1++;
     value = strtok(NULL,",");
   }
   fseek(fone, 0, SEEK_SET);
   //check column length
   while((line = fgets(buff, sizeof(buff),fone)) != NULL) {
     value = strtok(line,"\n");
     m1++;
   }
   fseek(fone, 0, SEEK_SET);
   //allocate memory
   mone = malloc(sizeof(int *) * m1);
   for (loop = 0; loop < m1; ++loop) {
     mone[loop] = malloc(sizeof(int) * n1);
   }
   //store elements into matrix
   while((line = fgets(buff, sizeof(buff),fone)) != NULL) {
     value = strtok(line,",");
     while(value != NULL) {
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
       mone[i][j++] = atof(value);
       value = strtok(NULL,",");
     }
     if (j != n1) {
       printf("ERROR: IMPROPERLY FORMED MATRIX\n");
       return -1;
     }
     ++i;
     j = 0;
   }
   fclose(fone);
   //matrix two
   //check number of columns
   line = fgets(buff,sizeof(buff),ftwo);
   value = strtok(line,",");
   while(value != NULL) {
     n2++;
     value = strtok(NULL,",");
   }
   fseek(ftwo, 0, SEEK_SET);
   //check number of rows
   while((line = fgets(buff, sizeof(buff),ftwo)) != NULL) {
   value = strtok(line,"\n");
   m2++;
   }
   fseek(ftwo, 0, SEEK_SET);
   //allocate memory
   mtwo = malloc(sizeof(int *) * n2);
   for (loop = 0; loop < n2; ++loop) {
     mtwo[loop] = malloc(sizeof(int) * m2);
   }
   //store elements in matrix
   i = 0;
   while((line = fgets(buff,sizeof(buff),ftwo)) != NULL) {
     value = strtok(line,",");
     while(value != NULL) {
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
       mtwo[i++][j] = atof(value); //done to avoid inefficiency during multiplication step
       value = strtok(NULL,",");
     }
     if (i != n2) {
       printf("ERROR: IMPROPERLY FORMED MATRIX\n");
       return -1;
     }
     ++j;
     i = 0;
   }
   fclose(ftwo);
   //allocate product matrix
   prod = malloc(sizeof(int *) * m1);
   for (loop = 0; loop < m1; ++loop) {
     prod[loop] = malloc(sizeof(int) * n2);
   }
   if (n1 != m2) {
     printf("ERROR: MATRICES CANNOT BE MULTIPLIED\n");
     return -1;
   }
   for (i = 0; i < m1; ++i) {
     for(j = 0; j < n2; ++j) {
       for(k = 0; k < n1; ++k) {
	 sum = sum+mone[i][k]*mtwo[j][k];
       }
       prod[i][j] = sum;
       sum = 0;
     }
   }
   ans = fopen("ans.csv","w");
   for (i = 0; i < m1; ++i) {
     for (j = 0; j < n2; ++j) {
       fprintf(ans, "%f", prod[i][j]);
       if (j != n2-1) {
	 fprintf(ans, "%s", ",");
       }
       else if (i != m1-1) {
	 fprintf(ans, "\n");
       }
     }
   }
   fclose(ans);
}
