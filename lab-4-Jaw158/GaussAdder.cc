#include <stdio.h>
#include <ctype.h>

void GaussAdder(long double n) {
  long double s;
  printf("I have begun adding the numbers from 1 to %.0Lf\n",n);
  s = n*(n+1)/2;
  printf("The sum of the integers from 1 to %d is: %.0Lf\n",(int) n,s);
}

main() {
  int c, n;
  printf("Please enter an integer: ");
  scanf("%d",&n);//inputs integer
  c = getchar(); //records number and type of characters
  while(1) { //run loop until the file ends
    if(isdigit(c)) {
      c = getchar(); //uses existing value for c after first time
    }
    else if(c == 10) { //10 is the indicator for EOF
      printf("The number entered is %d\n",n);
      GaussAdder(n);
      return 0;
      break; //stop loop
    }
    else {
      printf("ERROR: NOT AN INTEGER \n");
      return 1; //error code
      break;
    }
  }
}
