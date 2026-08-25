#include "lexer.h"
#include "parser.h"
#include "writer.h"
#include "data.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

FILE *input;
FILE *output;

int main(int argc, char *argv[])
{
    input = fopen(argv[1], "r");
    output = fopen("out.css", "w");
    lex(tokens, input);
    printf("kuronami vandal\n");
    for (int i = 0; tokens[i] != NULL; i++)
        printf("%s ", tokens[i]);
    parse(tokens);
}