#include <stdlib.h>
#include <stdio.h>

#define MAXTOKENCHAR 1001
#define MAXTOKENS 100

extern FILE *input, *output;
extern char *input_curline, *input_filename;

// Lexical Analyzer, Debug Informations (For lexer.h)
extern int dlexer_column, dlexer_linenum, dlexer_dlinenum, dlexer_dcolumn, dlexer_dcolumnend;
extern char *dlexer_line, *dlexer_dline;

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
char tokens[MAXTOKENCHAR][MAXTOKENS];