#ifndef OKML_H
#define OKML_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct okml okml;


// Dynamic array of okml pointers
typedef struct {
    struct okml** items;
    size_t count;
    size_t capacity;
} okml_array;


typedef struct okml {
    char* key;
    char* val_string;
    okml_array* child_list;
} okml;

// Function declarations (only prototypes)
okml_array* okml_array_create(void);
void okml_array_push(okml_array* arr, okml* element);
okml* okml_array_get(okml_array* arr, size_t index);
void okml_array_pop(okml_array* arr);
void okml_array_remove_at(okml_array* arr, size_t index);
void okml_array_free(okml_array* arr);

// Helper functions for okml nodes
okml* okml_create_node(void);
void okml_free_node(okml* node);
void okml_add_child(okml* parent, okml* child);


//HERE
bool has_char(char* line, char delim);
bool find_key_value(char* line, okml_array* arr);
char* get_name(const char* str, const char* delim);
FILE* find_child(FILE* file, okml_array* root, char* key);
// Forward Declarations for typecheck.c

void remove_whitespace(char *str);
void parse_line(okml* node, const char* line);

/* OKML Functions */
okml_array* okml_load(char* filename);
char* okml_find(okml_array* arr, char* key);

// Implementation of all the functions
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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

okml_array* okml_array_create(void) {
    okml_array* arr = (okml_array*)malloc(sizeof(okml_array));
    if (!arr) return NULL;
    
    arr->count = 0;
    arr->capacity = 4;
    arr->items = (okml**)malloc(sizeof(okml*) * arr->capacity);
    
    if (!arr->items) {
        free(arr);
        return NULL;
    }
    
    return arr;
}

void okml_array_push(okml_array* arr, okml* element) {
    if (!arr) return;
    
    if (arr->count >= arr->capacity) {
        arr->capacity *= 2;
        arr->items = (okml**)realloc(arr->items, sizeof(okml*) * arr->capacity);
    }
    arr->items[arr->count++] = element;
}

okml* okml_array_get(okml_array* arr, size_t index) {
    if (!arr || index >= arr->count) return NULL;
    return arr->items[index];
}

void okml_array_pop(okml_array* arr) {
    if (arr && arr->count > 0) {
        arr->count--;
    }
}

void okml_array_remove_at(okml_array* arr, size_t index) {
    if (!arr || index >= arr->count) return;
    
    for (size_t i = index; i < arr->count - 1; i++) {
        arr->items[i] = arr->items[i + 1];
    }
    arr->count--;
}

void okml_array_free(okml_array* arr) {
    if (arr) {
        free(arr->items);
        free(arr);
    }
}

okml* okml_create_node(void) {
    return (okml*)calloc(1, sizeof(okml));
}

void okml_free_node(okml* node) {
    if (!node) return;
    
    free(node->key);
    free(node->val_string);
    free(node);
}

bool find_key_value(char* line, okml_array* arr){
    
  bool found = false;
  int len = strlen(line);
  char* ss = malloc(sizeof(char) * (len + 1));

  okml* parsed_data = okml_create_node();


  for (int i = 0; i < len; ++i) {
    if(line[i] == ':'){
      found = true;
      strncpy(ss, line, i);
      ss[i] = '\0';
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


void remove_whitespace(char *str) {
    char *read = str;
    char *write = str;
    
    while (*read) {
        if (!isspace((unsigned char)*read)) {
            *write = *read;
            write++;
        }
        read++;
    }
    *write = '\0';
}

void parse_line(okml* node, const char* line) {
    if (node == NULL || line == NULL) return;
    
    // Trim whitespace
    while (isspace((unsigned char)*line)) line++;
    if (*line == '\0') {
        node->val_string = NULL;
        return;
    }
    
    const char* end = line + strlen(line) - 1;
    while (end > line && isspace((unsigned char)*end)) end--;
    
    int len = end - line + 1;
    char* trimmed = (char*)malloc(len + 1);
    strncpy(trimmed, line, len);
    trimmed[len] = '\0';
        
    // Default: treat as string

    node->val_string = trimmed; // trimmed will be freed elsewhere
}


bool has_char(char* line, char delim) {
  if(delim == '`') return strstr(line, "```") != NULL;
  return strchr(line, delim) != NULL;
}



char* get_name(const char* str, const char* delim) {
    char* copy = strdup(str);           // Copy to modifiable memory
    if (!copy) return NULL;
    
    char* token = strtok(copy, delim);  // Get first token
    char* result = token ? strdup(token) : NULL;  // Duplicate token
    
    free(copy);  // Free the copy
    return result;  // Return the token (caller must free)
}

#endif // OKML_H
