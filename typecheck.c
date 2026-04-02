#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct okml {
  char* key;
  char* val_string;
  int val_int;
  bool val_bool;
  int size;
  struct okml* sub_list;
} okml;

void parse_line(okml* node, const char* line) {
    if (node == NULL || line == NULL) return;
    
    // Trim whitespace
    while (isspace((unsigned char)*line)) line++;
    if (*line == '\0') {
        node->val_string = NULL;
        node->val_int = 0;
        node->val_bool = false;
        return;
    }
    
    const char* end = line + strlen(line) - 1;
    while (end > line && isspace((unsigned char)*end)) end--;
    
    int len = end - line + 1;
    char* trimmed = (char*)malloc(len + 1);
    strncpy(trimmed, line, len);
    trimmed[len] = '\0';
    
    // Check for boolean
    if (strcasecmp(trimmed, "true") == 0) {
        node->val_bool = true;
        node->val_string = NULL;
        node->val_int = 0;
        free(trimmed);
        return;
    }
    if (strcasecmp(trimmed, "false") == 0) {
        node->val_bool = false;
        node->val_string = NULL;
        node->val_int = 0;
        free(trimmed);
        return;
    }
    
    // Check for digit (single character)
    if (strlen(trimmed) == 1 && isdigit(trimmed[0])) {
        node->val_int = trimmed[0] - '0';
        node->val_string = NULL;
        node->val_bool = false;
        free(trimmed);
        return;
    }
    
    // Check for number (multiple digits)
    bool is_number = true;
    for (int i = 0; i < strlen(trimmed); i++) {
        if (!isdigit(trimmed[i])) {
            is_number = false;
            break;
        }
    }
    
    if (is_number && strlen(trimmed) > 0) {
        node->val_int = atoi(trimmed);
        node->val_string = NULL;
        node->val_bool = false;
        free(trimmed);
        return;
    }
    
    // Default: treat as string
    node->val_string = trimmed; // trimmed will be freed elsewhere
    node->val_int = 0;
    node->val_bool = false;
}
