#include <stdio.h>
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
