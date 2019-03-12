#include <stdio.h>
#include <ctype.h>
int n, i;
main () {
  printf("Hello! Please give me an integer: ");
  for(i = 0; i < 5; ++i) { //iterates loop 5 times
    n = getchar(); //input and analysis of each character
    while(i < 4) { //stops the loop after iteration 4
      if (isdigit(n)) { //checks if input is a number
	n = getchar(); //analyzes each character
      }
      else if (n == 10) { //code indicating end of file
	printf("Thanks! Please give me another integer: ");
	break; //ends only the while loop
      }
      else {
	printf("ERROR: NOT AN INTEGER \n");
	return 1; //ends code with an error
      }
    }
  }
  printf("Thanks! I am happy with five integers. \n");
  return 0;
}
