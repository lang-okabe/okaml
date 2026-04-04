#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "okml.h"

bool find_key_value(char* line, okml_array* arr){
    
  bool found = false;
  int len = strlen(line);
  char* ss = malloc(sizeof(char) * len);

  okml* parsed_data = okml_create_node();


  for (int i = 0; i < len; ++i) {
    if(line[i] == ':'){
      found = true;
      strncpy(ss, line, i);
      char* key = (strdup(ss));

      remove_whitespace(key);
      parsed_data->key = key;

      parse_line(parsed_data,strncpy(ss, line+i+1, len));
      
    }
  }

  okml_array_push(arr, parsed_data);
  return found;
}

FILE* find_child(FILE* file, okml_array* root, char* key) {
  char line[256];

  okml_array* child_list = okml_array_create();
  okml* parsed_data = okml_create_node();
  parsed_data->child_list=child_list;
  parsed_data->key=key;
  parsed_data->type="list";
  okml_array_push(root, parsed_data);
  
  /* Read the File line by line */
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';

    /* CHECK FOR NESTED LISTS */
    if (has_char(line, '{')) {
      char* sub_key = get_name(line, "{");
      remove_whitespace(sub_key);
      find_child(file, parsed_data->child_list, sub_key);
    }

    /* EXIT IF NEST END */
    if (has_char(line, '}')) {
      return file;
    }

    /* Send the line to find the key-value pair */
    find_key_value(line, child_list);
  
  }

  return file;
}

