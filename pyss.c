#include "data.h"
#include "lexer.h"
#include "parser.h"
#include "writer.h"

#include <stdio.h>
#include <stdlib.h>

FILE *input;
FILE *output;
char *curline;

int main(int argc, char *argv[])
{
    input = fopen("C:\\code\\Practice\\pyss\\style.pyss", "r");
    output = fopen("out.css", "w");
    curline = malloc(1001);
    fgets(curline, 1001, input);
    lex(input, curline);
    for (int i = 0; tokens[i][0] != '\0'; i++)
    printf("[%s] ", tokens[i]);
    parse();
    write(output);
    printf("succes\n");
    return 0;
}