#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "typecheck.c"
#include "helpers.c"
#include "okml.h"

okml pair;

void parse(char* filename){
  FILE* file = fopen(filename, "r");
  char line[256];
  if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
	  find_key_value(line,pair);

        }
        fclose(file);
    }
    else {
        fprintf(stderr, "Unable to open file!\n");
    }
}

int main(int argc, char *argv[])
{

  if(argc > 1){
    printf("file name -> %s\n", argv[1]);
  }
  parse(argv[1]);
  return 0;
}

