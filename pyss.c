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
    input = fopen("C:\\code\\Practice\\pyss\\pyss.exe", "r");
    if (input == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    lex(input);
    for (int i = 0; i < 1000; i++)
    {
        printf("%s%i", tokens[i], i);
    }
}