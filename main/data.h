#include <stdlib.h>
#include <stdio.h>

FILE *input;
FILE *output;
char *input_current_line;
char *input_filename = "style.pyss";

// Lexical Analyzer, Debug Informations
int dlexer_line = 0;
int dlexer_column = 0;
int dlexer_dline = 0;
int dlexer_dcolumn = 0;
int dlexer_dcolumnend = 0;

/* Node Struct containing
    type (selector, property, comment)
    name (data about the top level name either root in def or property name)
    value (empty if type is selector but contain value if it's property. the value of the property)
    ident (identation or total \t characters before value)*/
typedef struct NODE
{
    char *type;
    char *parent;
    char *name;
    char *value;
    int indent;
} NODE;

NODE node;

// Global Variables
// Tokens lexer will use and other functions will obtain
char tokens[1000][100];