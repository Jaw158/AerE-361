#include <stdio.h>
#include <string.h>

main(int argc, char* argv[]) {
  long double x1, x2, xn;
  int loop, n = 10;
  if (argc == 2) {
    if (strcmp(argv[1],"-d") == 0) {
      n = 20;
    }
  }
  else if (argc > 2) {
    printf("ERROR: TOO MANY COMMAND LINE ARGUMENTS\n");
    return 1;
  }
  x1 = 11.0/2.0;
  x2 = 61.0/11.0;
  for (loop = 0; loop < n; ++loop) {
    printf("Term %d: %Lf\n",loop+1,x1);
    if (x1 < 0) {
      printf("ERROR: VALUES SHOUDL ALWAYS BE POSITIVE\n");
      return 1;
    }
    else if (x2 < x1) {
      printf("ERROR: VALUES SHOULD ALWAYS BE INCREASING\n");
      return 1;
    }
    else if (x1 > 6) {
      printf("ERROR: VALUES SHOULD NOT EXCEED SIX\n");
    }
    xn = ((111*x2+3000/x1)-1130)/x2;
    x1 = x2;
    x2 = xn;
  }
}
