#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "typecheck.c"
typedef struct okml {
  char* key;
  char* val_string;
  int val_int;
  bool val_bool;
  
  int size;
  struct okml* sub_list;

} okml;

okml parsed_data;



bool find_key_value(char* line){
  int len = strlen(line);
  char* ss = malloc(sizeof(char) * len);
  char* key = malloc(sizeof(char) * len);
  char* value = malloc(sizeof(char) * len);
  for (int i = 0; i < len; ++i) {
    if(line[i] == ':'){
      /* printf("%s = ", strncpy(ss, line, i) ); */
      /* printf("%s\n", strncpy(ss, line+i+1, len)); */
      parse_line(&parsed_data, line);
      parsed_data.size++;
      printf("-> %s \n" , parsed_data.val_string);
    }
  }
}

void parse(char* filename){
  FILE* file = fopen(filename, "r");
  char line[256];
  if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            /* printf("-> %s", line); */
	  find_key_value(line);

        }
        fclose(file);
    }
    else {
        fprintf(stderr, "Unable to open file!\n");
    }
}

int main(int argc, char *argv[])
{
  parse("syntax.okml");
  return 0;
}

