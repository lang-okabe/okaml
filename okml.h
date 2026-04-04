// okml.h
#ifndef OKML_H
#define OKML_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct okml {
    char* key;
    char* type;
    
    char* val_string;
    int val_int;
    bool val_bool;
    
    struct okml** child;
    size_t children_count;
    size_t children_capacity;
} okml;

// Dynamic array of okml pointers
typedef struct {
    okml** items;
    size_t count;
    size_t capacity;
} okml_array;

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

// Forward Declarations for typecheck.c

void remove_whitespace(char *str);
void parse_line(okml* node, const char* line);

#endif // OKML_H
