#include "helper/data.h"
#include "helper/lexer.h"
#include "helper/parser.h"
#include "helper/writer.h"

#include <stdio.h>
#include <stdlib.h>

FILE *input;
FILE *output;
char *curline;

int main(int argc, char *argv[])
{
    input = fopen("C:\\code\\Practice\\pyss\\test\\style.pyss", "r");
    output = fopen("test\\out.css", "w");
    curline = malloc(1001);
    while (fgets(curline, 1001, input) != NULL)
    {
        // printf("%s", strip(curline));
        lex(input, curline);
        for (int i = 0; tokens[i][0] != '\0'; i++) {
            printf("[%s] ", tokens[i]);
        }
        printf("\n");
    }
    return 0;
}