#include "main/data.h"
#include "main/lexer.h"
#include "main/parser.h"
#include "main/writer.h"

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
        sublex(input, curline);
        if (tokens[0][0] != '\0')
        {
            printf("[%i] ", tokens[0][0]);
            for (int i = 1; tokens[i][0] != '\0'; i++) {
                printf("[%s] ", tokens[i]);
            }
            printf("\n");
        }
    }
    return 0;
}