#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "helpers.c"
#include "finder.c"
#include "okml.h"

okml_array* okml_load(char* filename){
  okml_array* arr = okml_array_create();
  FILE* file = fopen(filename, "r");
  char line[256];
  if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {

	  if(has_char(line,':')){
	    find_key_value(line,arr);
	  }
	  
	  if(has_char(line, '{')){
	    char* key = get_name(line, "{");
	    remove_whitespace(key);
	    find_child(file,arr, key);
	  }
        }
        fclose(file);
  }
  else {
      fprintf(stderr, "Unable to open file!\n");
    }
  
  return arr;
}

char* okml_find(okml_array* arr,  char* key){
  if (!arr || !arr->items) exit(-1);
  int N = arr->count;
  for (int i = 0; i < N; ++i) {
    okml *it = arr->items[i];
    if (!it) continue;

    if (it->key && strcmp(it->key, key) == 0) {
      if(it->val_string == NULL && it->child_list != NULL){
	fprintf(stderr, "Key %s has a list as a value\n", key);
	exit(-1);
      }
      char* rc = strdup(it->val_string);
      return rc;
    }
    if (it->val_string == NULL && it->child_list != NULL) {
      char* rc = okml_find(it->child_list, key);
      if(rc != NULL){
	return rc;
      }
    }
  }
  
  return NULL;
}

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


