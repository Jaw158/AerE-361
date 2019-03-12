/*
this is an unholy combination of various different codes, some written by the professor, some by me, and some provided in the lab directory. I will be genuinely surprised if it works.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "csv.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define flagBufLength 10

struct counts {
  long unsigned fields;
  long unsigned rows;
};

void cb1 (void *s, size_t len, void *data) {
  ((struct counts *)data)->fields++;
}
void cb2 (int c, void *data) { ((struct counts *)data)->rows++; }

static int is_space(unsigned char c) {
  if (c == CSV_SPACE || c == CSV_TAB) return 1;
  return 0;
}

static int is_term(unsigned char c) {
  if (c == CSV_CR || c == CSV_LF) return 1;
  return 0;
}

void printUsage(void) {
	fprintf(stderr, "Usage: InputSanitizer ([-s AString | -n ANumber | -c ACharacter]) \n");
	fprintf(stderr, "\twhere: \n");
	fprintf(stderr, "\t   AString contains 10 or fewer characters with no spaces,\n");
	fprintf(stderr, "\t   ANumber is an integer less than 100.\n");
	fprintf(stderr, "\t   ACharacter is a single alpha character.\n");
	fprintf(stderr, "\t Note: the program accepts a maximum of ONE input of each type\n\n");
	exit(1); /*kill the program now if the user can't figure out how to run it*/
} /*end printUsage*/

int
main (int argc, char *argv[])
{

 /***** Variable Declarations *****/
  char MyString[10];
  char MyNumberString[4];
  char MyCharString[4];
  short MyNumber;
  char MyChar;
  char flagBuf[flagBufLength]; /*a buffer for input flags*/

  short GotNumber = 0;         /*Did we get a number as input?*/
  short GotString = 0;         /*Did we get a string as input?*/
  short GotChar = 0;           /*Did we get a character as input?*/

  short i, j;                  /*iterative variables*/
  


  /*****************************************************************/
  /***** Error Checking *****/
  /*****************************************************************/
  
  /* First, set defaults */
  /* ALWAYS INITIALIZE YOUR VARIABLES!!!*/
  strcpy(flagBuf, "");
  strcpy (MyString, "");
  strcpy (MyNumberString, "");
  strcpy (MyCharString, "");
  MyNumber = -1;
  MyChar = '\0';
  GotString = 0;
  GotNumber = 0;
  GotChar = 0;


  /*Check for the correct number of command-line arguments*/

  if ( (argc == 1) /*got only the name of the program*/
       || ( argc%2 != 1 ) /*don't have an odd number of arguments*/
       || ( (argc == 2) && (strcmp(argv[1], "--help") == 0) ) ) {
    printUsage();
  } /*end if*/

  for (i = 1; i < argc-1; i = i + 2) {
	
    /*printf("Top of loop: i is: %d\n", i);*/

	/*Error checking: make sure the flag is not too long*/
	if (strlen(argv[i]) > flagBufLength-1) {
	    fprintf(stderr, "ERROR: Expecting a (shorter) flag of the form -flag; Got \'%s\'\n",
		    argv[i]);
	    printUsage();
	} /*end if*/

	strcpy(flagBuf, argv[i]); /*copy the flag into a buffer so we can parse it*/
	
	if (flagBuf[0] != '-') {
	    fprintf(stderr, "ERROR: Expecting a flag of the form -flag; Got \'%s\'\n",
		    flagBuf);
	    printUsage();
	} /*end if*/
	
	switch (flagBuf[1]) {
	case 'c' : 
	case 'C' :
	  if ((strcmp(flagBuf, "-c") == 0) 
	      || (strcmp(flagBuf, "-C") == 0)) {
	    if (GotChar == 1) { /*Check that this is the first character*/
	      fprintf(stderr, "ERROR: Received more than one character\n");
	      printUsage();
	    } /*end if*/
	    
	    /*Record this character*/
	    GotChar = 1;

	    strcpy(MyCharString, argv[i+1]); /*copy the character into a string so we can parse it*/
	    printf ("Got char: %s\n", MyCharString); 
	    
	    if ( (strlen(MyCharString) > 1)
		 || (isalpha(MyCharString[0]) == 0) ) {
	      fprintf(stderr, "This is not a valid character: %s\n", MyCharString);
	      printUsage();
	    } /*end if*/
	    /*Note: if we get here, we have a valid character*/
	    MyChar = MyCharString[0]; /*copy out the character for easy reference*/
	    
	  } /*end if*/
	  else {
	    fprintf(stderr, "Unrecognized flag1 \'%s\'\n", flagBuf);
	    printUsage();
	  } /*end else*/
	  break;

	case 'n' :
	case 'N' :
	  if ((strcmp(flagBuf, "-n") == 0) 
	      || (strcmp(flagBuf, "-N") == 0)) {
	    if (GotNumber == 1) { /*Check that this is the first number*/
	      fprintf(stderr, "ERROR: Received more than one number\n");
	      printUsage();
	    } /*end if*/
	    
	    /*Record this number*/
	    GotNumber = 1;
	    strcpy(MyNumberString, argv[i+1]); /*copy the number into a string so we can parse it*/
	    
	    j = 0; /*start the loop iterator at 0*/
	    while (MyNumberString[j] != '\0') { /*while we are not at the end of the string*/
	      /*Note, we should probably check that j is less than the string length too!*/
	      if (isdigit(MyNumberString[j]) == 0 ) {
		fprintf(stderr, "This is not a valid number: %s\n", MyNumberString);
		printUsage();
	      } /*end if*/
	      j++; /*remember to increase the loop iterator!*/
	    } /*end while*/
	    /*Note: if we get to this line of code, then we know we have a number!*/
	    /*Now, record the number*/
	    MyNumber = atoi(MyNumberString); 
	    
	  } /*end if*/
	  else {
	    fprintf(stderr, "Unrecognized flag1 \'%s\'\n", flagBuf);
	    printUsage();
	  } /*end else*/
	  break;
	  
	case 's' :
	case 'S' :
	  if ((strcmp(flagBuf, "-s") == 0) 
	      || (strcmp(flagBuf, "-S") == 0)) {
	    if (GotString == 1) { /*Check that this is the first string*/
	      fprintf(stderr, "ERROR: Received more than one string\n");
	      printUsage();
	    } /*end if*/
	    
	    /*Record this string*/
	    GotString = 1;
	    strcpy(MyString, argv[i+1]); /*copy the string out to save it*/
	    
	    if (! (strlen(MyString) > 0)) { /*check that the string is not empty*/
	      fprintf(stderr, "Error: got an empty string!\n");
	      printUsage();
	    } /*end if*/
	    
	  } /*end if*/
	  else {
	    fprintf(stderr, "Unrecognized flag1 \'%s\'\n", flagBuf);
	    printUsage();
	  } /*end else*/

	  /*Note: at this point we should have a valid string*/
	  break;
	  
	default : /*In case the user did something else we didn't expect...*/
	  printUsage(); 
	} /*end switch*/
	
	/*printf("Bottom of loop: i is: %d\n", i);*/

  } /*end for*/
  /*i is argc-1 now*/


  printf("Yay! You can specify correct inputs: \n");
  if (GotChar) {
    printf("\tGot this (correct) character: %c\n", MyChar);
  } /*end if*/
  if (GotNumber) {
    printf("\tGot this (correct) number: %d\n", MyNumber);
  } /*end if*/
  if (GotString) {
    printf("\tGot this (correct) string: %s\n", MyString);
  } /*end if*/

    return 0;
  
  FILE *fp;
  struct csv_parser p;
  char buf[1024];
  size_t bytes_read;
  unsigned char options = 0;
  struct counts c = {0, 0};

  if (argc < 2) {
    fprintf(stderr, "Usage: csvinfo [-s] files\n");
    exit(EXIT_FAILURE);
  }

  if (csv_init(&p, options) != 0) {
    fprintf(stderr, "Failed to initialize csv parser\n");
    exit(EXIT_FAILURE);
  }

  csv_set_space_func(&p, is_space);
  csv_set_term_func(&p, is_term);

  while (*(++argv)) {
    if (strcmp(*argv, "-s") == 0) {
      options = CSV_STRICT;
      csv_set_opts(&p, options);
      continue;
    }

    fp = fopen(*argv, "rb");
    if (!fp) {
      fprintf(stderr, "Failed to open %s: %s\n", *argv, strerror(errno));
      continue;
    }

    while ((bytes_read=fread(buf, 1, 1024, fp)) > 0) {
      if (csv_parse(&p, buf, bytes_read, cb1, cb2, &c) != bytes_read) {
        fprintf(stderr, "Error while parsing file: %s\n", csv_strerror(csv_error(&p)));
      }

    csv_fini(&p, cb1, cb2, &c);

    if (ferror(fp)) {
      fprintf(stderr, "Error while reading file %s\n", *argv);
      fclose(fp);
      continue;
    }

    int u, v, loop;
    int **mat;
    int n = c.rows, m = c.fields/c.rows;
    
  mat = malloc(sizeof(int *) * n);
  for(loop = 0; loop < n; ++loop){
    mat[loop] = malloc(sizeof(int) * m);
  }
  for (v = 0; v < n; ++v) {
    for (u = 0; u < m; ++u) {
      mat[u][v] = (int) fp;
    }
  }

 printf("Output: \n");
  for (v = 0; v < n; ++v) {
    for (u = 0; u < m; ++u) {
      printf("%d ",mat[u][v]);
    }
    printf("\n");
  }

    fclose(fp);
    printf("%s: %lu fields, %lu rows\n", *argv, c.fields, c.rows);
  }
  }
 
   
  csv_free(&p);
  exit(EXIT_SUCCESS);
}
