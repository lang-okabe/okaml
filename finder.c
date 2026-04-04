#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "okml.h"

bool find_key_value(char* line, okml_array* arr){
  okml* parsed_data = okml_create_node();
    
  bool found = false;
  int len = strlen(line);
  char* ss = malloc(sizeof(char) * len);

  for (int i = 0; i < len; ++i) {
    if(line[i] == ':'){
      found = true;
      strncpy(ss, line, i);
      char* key = (strdup(ss));

      remove_whitespace(key);
      parsed_data->key = key;

      parse_line(parsed_data,strncpy(ss, line+i+1, len));
      
      printf("%s -> ", parsed_data->key );
      if(parsed_data->val_string != NULL){
	printf("%s", parsed_data->val_string);
      } else {
	printf("%s", parsed_data->val_bool ? "true" : "false");
      }
      printf(" || Type -> %s\n", parsed_data->type);
    }
  }

  okml_array_push(arr, parsed_data);
  return found;
}

FILE* find_child(FILE* file, okml_array* root, char* key) {
  char line[256];
  okml_array* child_list = okml_array_create();
  printf("[SUBLIST ENT] - %s \n", key);
  /* Read the File line by line */
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';

    /* CHECK FOR NESTED LISTS */
    if (has_char(line, '{')) {
      char* sub_key = get_name(line, "{");
      remove_whitespace(sub_key);
      find_child(file, root, sub_key);
    }

    /* EXIT IF NEST END */
    if (has_char(line, '}')) {
      printf("[SUBLIST END] - %s\n", key);
      return file;
    }

    /* Send the line to find the key-value pair */
    find_key_value(line, root);
  
  }

  printf("[SUBLIST END] - %s\n", key);  
  return file;
}

