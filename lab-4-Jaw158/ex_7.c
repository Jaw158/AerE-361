#include <stdio.h>
main() {
  int c;
  c = getchar(); //both requests input and checks each character
  while(1) { //run loop until the file ends
    if(c >= '0' && c <= '9') {
      c = getchar(); //uses existing value for c after first time
    }
    else if(c == 10) { //10 is the indicator for EOF
      printf("That is an integer \n");
      return 0;
      break; //stop loop
    }
    else {
      printf("That is not an integer \n");
      return 1; //error code
      break;
    }
  }
}
