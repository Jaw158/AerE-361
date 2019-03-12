#include <stdio.h>
#include <ctype.h>

void BruteForceAdder(int n) {
  long double s, i;
  s = 0;
  printf("I have begun adding the numbers from 1 to %d\n",n);
  for(i = 1; i <= n; i = ++i) {
    s = s+i;
  }
  printf("The sum of the integers from 1 to %d is: %.0Lf\n",n,s);
}
  
main() {
  int c;
  long n;
  printf("Please enter an integer: ");
  scanf("%ld",&n);//inputs integer
  c = getchar(); //records number and type of characters
  while(1) { //run loop until the file ends
    if(isdigit(c)) {
      c = getchar(); //uses existing value for c after first time
    }
    else if(c == 10) { //10 is the indicator for EOF
      printf("The number entered is: %ld\n",n);
      BruteForceAdder(n);
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
