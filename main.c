#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "helpers.c"
#include "finder.c"
#include "okml.h"



void parse(char* filename){
  okml_array* arr = okml_array_create();
  FILE* file = fopen(filename, "r");
  char line[256];
  if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
	  if(has_char(line,':')){
	    find_key_value(line,arr);
	  }
	  if(has_char(line, '{')){
	    find_child(file,arr, "key");
	  }
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

