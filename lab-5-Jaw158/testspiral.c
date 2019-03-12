#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

spiral(n, **mat) {
  int n2, i, x, y, loop, count, direct;
  count = 0;
  direct = 1;
  i = 1;
  n2 = n*n;
  x = (n-1)/2;
  y = x;
  mat[x][y] = i;
  printf("%d %d %d\n",i,x,y);
  ++i;  
  while (1) {
    ++count;
    for (loop = 0; loop < count; ++loop) {
      x = x+direct;
      mat[x][y] = i;
      printf("%d %d %d\n",i,x,y);
      if (i == n2) {
	return 0;
      }
      ++i;
    }
    for (loop = 0; loop < count; ++loop) {
      y = y + direct;
      mat[x][y] = i;
      printf("%d %d %d\n",i,x,y);
      if (i == n2) {
	return 0;
      }
      ++i;
    }
    direct = direct*-1;
  }
}
  
main() {
  int n, loop;
  int **mat;
  scanf("%d",&n);
  mat = malloc(sizeof(int *) * n);
  for(loop = 0; loop < n; ++loop){
    mat[loop] = malloc(sizeof(int) * n);
  }
  spiral(n, **mat);
}


