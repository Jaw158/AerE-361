#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n, i;
  int *foo; //pointer
  printf("Enter a number: ");
  scanf("%d",&n);

  foo = malloc(sizeof(int) * n);

  for (i = 0; i < n; ++i) {
    printf("Number %d: ", i+1);
    scanf("%d", &foo[i]);
  }

  for (i = 0; i < n; ++i) {
    printf("%d\n", foo[i]);
  }
  return 0;
}
    
