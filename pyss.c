#include "data.h"
#include "lexer.h"
#include "parser.h"
#include "writer.h"

#include <stdio.h>
#include <stdlib.h>

FILE *input;
FILE *output;

int main(int argc, char *argv[])
{
    input = fopen("C:\\code\\Practice\\pyss\\style.pyss", "r");
    output = fopen("out.css", "w");
    lex(input);
    printf("[%s] ", tokens[i]);
    parse();
    write(output);
    printf("succes\n");
    return 0;
}