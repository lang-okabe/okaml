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
      strncpy(ss, line, i);
      char* key = (strdup(ss));

      remove_whitespace(key);
      parsed_data.key = key;

      parse_line(&parsed_data,strncpy(ss, line+i+1, len));
      parsed_data.size++;
      
      printf("%s -> ", parsed_data.key );
      if(parsed_data.val_string != NULL){
	printf("%s\n" , parsed_data.val_string);	
      } else {
	printf("%b\n", parsed_data.val_bool );
      }
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
    printf("size -> %d\n",parsed_data.size );

}

int main(int argc, char *argv[])
{
  parse("syntax.okml");
  return 0;
}

