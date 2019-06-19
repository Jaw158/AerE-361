#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  FILE *input, *ans;
  char buf[255], buf2[255], store[255], *title;
  int i, j, count, space = 0, spot = 0;
  int numR, a = 0, b;
  long double V, Va, Vb;

  if (argc != 2) {
    printf("ERROR: EXPECTED ONE FILE\n");
    return -1;
  }
  /*
  title = "grep -c 'R = ' ";
  printf("%s\n",argv[1]);
  printf("%s\n",title);
  strcat(title, argv[1]);
  */
  input = popen("grep -c 'R = ' path/to/input.dot","r");
  fgets(buf, sizeof buf, input);
  numR = atoi(buf); //number of resistors
  //printf("here: %d\n",numR);
  pclose(input);
  
  //stores poistion and resistance of each resistor
  /*resistors = malloc(sizeof(int *) * 4);
  for (i = 0; i < 4; ++i) {
    resistors[i] = malloc(sizeof(int) * numR+1);
  }*/

  for (i = 0; i < 255; i++) {
    store[i] = '\0';
  }
  
  long double resistors[3][numR], circuit[numR][numR+1], I[numR];
  input = popen("grep 'R = ' path/to/input.dot","r");
  while (fgets(buf, sizeof buf, input) != NULL) {
    //printf("%s",buf);
    count = 0;
    for (i = 0; i < strlen(buf); ++i) {
      if ((buf[i] >= '0' && buf[i] <= '9') || buf[i] == '.') {
	store[spot] = buf[i];
	spot++;
      }
      else if (strlen(store) != 0) {
	if (count == 0) {
	  resistors[0][space] = atoi(store);
	}
	else if (count == 1) {
	  resistors[1][space] = atoi(store);
	}
	else if (count == 2) {
	  resistors[2][space] = atof(store);
	}
	//printf("%f %d %d\n",atof(store), count, space);
	count++;
	for (j = 0; j < spot; ++j) {
	  store[j] = '\0';
	}
	spot = 0;
      }
    }
    //printf("\n");
    //printf("%Lf\n",resistors[2][0]);
    space++;
  }
  pclose(input);
  
  //finds voltage of circuit
  input = popen("grep 'V = ' path/to/input.dot","r");
  space = 0;
  while (fgets(buf, sizeof buf, input)  != NULL) {
    for (i = 0; i < strlen(buf); ++i) {
      if ((buf[i] >= '0' && buf[i] <= '9') || buf[i] == '.') {
	store[spot] = buf[i];
	spot++;
      }
      else if (strlen(store) != 0) {
	if (space == 0) {
	  Va = atof(store);
	}
	else if (space == 1) {
	  Vb = atof(store);
	}
	else {
	  printf("That shouldn't be possible...\n");
	  return -1;
	}
	//printf("%s %d %d\n",store, count, space);
	for (j = 0; j < spot; ++j) {
	  store[j] = '\0';
	}
	spot = 0;
      }
    }
    space++;
  }
  pclose(input);
  V = Va-Vb;
  //printf("%Lf\n",V);

  /*
  //matrix for solving Gauss-Jordan
  circuit = malloc(sizeof(int *) * numR);
  for (i = 0; i < numR; ++i) {
    circuit[i] = malloc(sizeof(int) * numR);
  }
  /*
  for (i = 0; i < 3; ++i) {
    for (j = 0; j < numR; ++j) {
      printf("%Lf ",resistors[i][j]);
    }
    printf("\n");
  }
  */
  i = 0;
  j = 0;
  
  for (i = 2; i < numR; ++i) {
    for (j = 0; j < numR; ++j) {
      //printf("%d %d",i-2,j);
      if (resistors[0][j] == i) {
	circuit[i-2][j] = -1;
	//printf(" -1");
      }
      else if (resistors[1][j] == i) {
	circuit[i-2][j] = 1;
	//printf(" 1");
      }
      else {
	circuit[i-2][j] = 0;
      }
      //printf("\n");
    }
  }
  for (i = 0; i < numR; ++i) {
    circuit[i][numR] = 0;
  }

  for (i = numR-2; i < numR; ++i) {
    for (j = 0; j < numR; ++j) {
      circuit[i][j] = 0;
    }
    circuit[i][numR] = V;
  }

  //identifies voltage sums in kirchhoff loop
  input = popen("grep '// ' path/to/input.dot","r");
  space = 0;
  while (fgets(buf2, sizeof buf2, input) != NULL) {
    a = 0;
    //printf("%s %d %d",buf2,a,space);
    for (i = 0; i < strlen(buf2); ++i) {
      if ((buf2[i] >= '0' && buf2[i] <= '9') || buf2[i] == '.') {
	store[spot] = buf2[i];
	spot++;
      }
      else if (strlen(store) != 0) {
	//a and b specify the lines
	b = a;
        a = atoi(store);
	for (j = 0; j < spot; ++j) {
	  store[j] = '\0';
	}
	spot = 0;
	//printf("%d %d\n",a,b);
	if (b == 0) {
	}
       	else {
	  //checks resistor matrix for resistors in between the nodes
	  for (j = 0; j < numR; ++j) {
	    //places resistance in circuit, sign depends on positive current direction and kirchhoff loop
	    if (resistors[0][j] == b && resistors[1][j] == a) {
	      circuit[numR-2+space][j] = resistors[2][j];
              //printf("here: %d  %d %d\n",j,b,a);
	    }
	    else if (resistors[0][j] == a && resistors[1][j] == b) {
	      circuit[numR-2+space][j] = -1*resistors[2][j];
	    }
	  }
	}
      }
    }
    space++;
  }
  pclose(input);

  /*
  for (i = 0; i < numR; ++i) {
    for (j = 0; j < numR+1; ++j) {
      printf("%Lf ", circuit[i][j]);
    }
    printf("\n");
  }
  */
  
  for (i = 0; i < numR; ++i) {
    for (j = 0; j < numR; ++j) {
      if (i != j) {
	/*
	if (circuit[i][j] == 0) {
	  for (count = j+1; count < numR; ++count) {
	    if (circuit[count][j] != 0) {
	      for (spot = 0; spot <= numR; spot++) {
		b = circuit[j][spot];
		circuit[j][spot] = circuit[count][spot];
		circuit[count][spot] = b;
	      }
	      for (spot = 0; spot <= 3; spot++) {
		b = resistors[spot][j];
		resistors[spot][j] = resistors[spot][count];
		resistors[spot][count] = b;
	      }
	    }
	  }
	}
	*/
	if (circuit[i][j] == 0) {
	  continue;
	}
	a = circuit[i][j];
	for (space = 0; space <= numR; ++space) {
	  b = circuit[j][space]-(circuit[j][j]*circuit[i][space])/a;
	  circuit[i][space] = b;
	}
      }
    }
  }
  for (i = 0; i < numR; ++i) {
    I[i] = circuit[i][numR]/circuit[i][i];
    //printf("%Lf\n",I[i]);
  }

  ans = fopen("ans.dot","w");
  fprintf(ans,"diagraph {\n");
  fprintf(ans,"    node [shape = box];\n");
  fprintf(ans,"    1 [label = \"V = %Lf\"];\n",Va);
  fprintf(ans,"    %d [label = \"V = %Lf\"];\n",numR,Vb);
  for (i = 0; i < numR; ++i) {
    fprintf(ans,"    %.Lf -> %.Lf [label = \"I = %.4Lf\"];\n",resistors[0][i],resistors[1][i],I[i]);
  }
  fprintf(ans,"}");
  fclose(ans);
}
