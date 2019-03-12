#include <stdio.h>
#include <ctype.h>
int k, c, n, i, j;
main () {
  printf("Hello! how many chars should I take: ");
  scanf("%d",&n);
  k = getchar();
  while(1) {
    if (isdigit(k)) {
      k = getchar();
    }
    else if (k == 10) {
      break;
    }
    else {
      printf("ERROR: NOT AN INTEGER \n");
      return 1;
    }
  }
  if (n != 0) {
    printf("Please give me a char: ");
  }
  for(i = 0; i <= n-1; ++i) { //iterates loop n times
    c = getchar();
    j = 0;
    while (1) {
      j++;
      c = getchar();
      if (j > 1) {
	printf("ERROR: MORE THAN ONE CHAR \n");
	return 2;
      }
      else if (c == 10 && i != n-1) {
	printf("Thanks! Please give me another char: ");
	break;
      }
      else if (c == 10 && i == n-1) {
	break;
      }
    }
  }
  printf("Thanks! I am happy with %d chars. \n",n);
  return 0;
}
