#include <stdio.h>
#include "okml.h"

/* SOME DRIVER CODE */
int main(int argc, char *argv[])
{

  if(argc > 1){
    printf("[IO] opening file %s\n\n", argv[1]);
  } 

  okml_array* okml = okml_load(argv[1]);
  char* rc = okml_find(okml, "isSubSub");
  printf("[RETURN] %s\n",rc );
  return 0;
}


