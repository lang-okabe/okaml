#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "okml.h"


bool find_key_value(char* line, okml parsed_data){

  bool found = false;
  int len = strlen(line);
  char* ss = malloc(sizeof(char) * len);

  for (int i = 0; i < len; ++i) {
    if(line[i] == ':'){
      found = true;
      strncpy(ss, line, i);
      char* key = (strdup(ss));

      remove_whitespace(key);
      parsed_data.key = key;

      parse_line(&parsed_data,strncpy(ss, line+i+1, len));
      
      printf("%s -> ", parsed_data.key );
      if(parsed_data.val_string != NULL){
	printf("%s", parsed_data.val_string);
      } else {
	printf("%b", parsed_data.val_bool );
      }
      printf(" || Type -> %s\n", parsed_data.type);
    }
  }
  return found;
}
