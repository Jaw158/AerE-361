#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
  
main() {
  int n, n2, i, x, y, u, v, loop, count, direct, size, square, k;
  int **mat;
  printf("Input: ");
  scanf("%d",&n);
  k = getchar();
  while(k != 10) {
    if (isdigit(k)) {
    }
    else {
      printf("ERROR: NOT AN INTEGER\n");
      return 1;
    }
  }
  if (n < 1 || n > 100) {
    printf("ERROR: NOT BETWEEN 1 and 100\n");
    return 2;
  }
  n2 = n*n;
  square = n2;
  size = 0;
  while(square) {
    square = square/10;
    ++size;
  }
  mat = malloc(sizeof(int *) * n);
  for(loop = 0; loop < n; ++loop) {
    mat[loop] = malloc(sizeof(int) * n);
  }
  count = 0;
  direct = 1;
  i = 1;
  x = (n-1)/2;
  y = x;
  mat[x][y] = i;
  while (1) {
    ++count;
    for (loop = 0; loop < count; ++loop) {
      ++i;
      if (i > n2) {
	break;
      }      
      x = x+direct;
      mat[x][y] = i;
    }
    for (loop = 0; loop < count; ++loop) {
      ++i;
      if (i > n2) {
	break;
      }
      y = y + direct;
      mat[x][y] = i;
    }
    if (i >= n2) {
      break;
    }
    direct = direct*-1;
  }
  printf("Output: \n");
  for (v = 0; v < n; ++v) {
    for (u = 0; u < n; ++u) {
      printf("%*d ",size,mat[u][v]);
    }
    printf("\n");
  }
  return 0; 
}


