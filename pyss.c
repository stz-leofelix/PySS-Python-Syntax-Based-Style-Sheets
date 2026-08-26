#include "data.h"
#include "lexer.h"
#include "parser.h"
#include "writer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

FILE *input;
FILE *output;

int main(int argc, char *argv[])
{
    FILE *input = fopen("style.pyss", "r");
    lex(input);
    for (int i = 0; i < 1000; i++)
    {
        printf("%s%i", tokens[i], i);
    }
}