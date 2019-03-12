#include <stdio.h>

int main (int argc, char **argv){
  int i = 0; //loop variable
  for (i = 0; i < argc; i ++){
    printf ("argument %d: %s\n", i, argv[i]);
  }
  return 0;
}
