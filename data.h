#include <stdio.h>
#include <stdlib.h>

/* Node Struct containing
    type (selector, property, comment)
    name (data about the top level name either root in def or property name)
    value (empty if type is selector but contain value if it's property. the value of the property)
    ident (identation or total \t characters before value)*/
typedef struct NODE
{
    char *type;
    char *name;
    char *value;
    int ident;
} NODE;

NODE node;

// Global Variables
// Tokens lexer will use and other functions will obtain
char tokens[1000][100];