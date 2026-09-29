#include "main/data.h"
#include "main/lexer.h"
#include "main/parser.h"
#include "main/writer.h"
#include "main/error.h"

#include <stdio.h>
#include <stdlib.h>

FILE *input = NULL;
FILE *output = NULL;
char *input_curline = NULL;
char *input_filename = NULL;

int dlexer_column = 1;
int dlexer_linenum = 1;
int dlexer_dlinenum = 1;
int dlexer_dcolumn = 1;
int dlexer_dcolumnend = 1;
char *dlexer_line = NULL;
char *dlexer_dline = NULL;

int main(int argc, char *argv[])
{
    // fprintf(stderr, BOLD RED"ParserError "RESET"style.pyss:22:0:16\n");
    // dprintln("bckaground-color: blue", 22, 0, 16);
    // fprintf(stderr, BOLD RED"Unknown identifier "BOLD GREEN"`%s`"RESET, "bckaground-color");
    input = fopen("C:\\code\\Practice\\pyss\\test\\style.pyss", "r");
    output = fopen("test\\out.css", "w");
    input_curline = malloc(1001);
    while (fgets(input_curline, 1001, input) != NULL)
    {
        lex(input, input_curline);
        if (tokens[1][0] != '\0' && fatality == 0)
        {
            printf("[%i] ", tokens[0][0]);
            for (int i = 1; tokens[i][0] != '\0'; i++)
                printf("[%s] ", tokens[i]);
            printf("\n");
        }
    }
    return 0;
}