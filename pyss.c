#include "main/data.h"
#include "main/lexer.h"
#include "main/parser.h"
#include "main/writer.h"
#include "main/error.h"

#include <stdio.h>
#include <stdlib.h>

// Runtime Informations
FILE *input = NULL;
FILE *output = NULL;
char *input_curline = NULL;
char *input_filename = NULL;

int dlexer_column = 1;
int dlexer_linenum = 0;
int dlexer_dlinenum = 0;
int dlexer_dcolumn = 0;
int dlexer_dcolumnend = 0;
char *dlexer_line = NULL;
char *dlexer_dline = NULL;

// Build Information
#define BUILD_VERSION 26.1.1
#define BUILD_CHANNEL "EarlyDevelopment"

int main(int argc, char *argv[])
{
    switch (argc) {
        case 1:
            #if defined(_WIN32)
                input = fopen("C:\\code\\Practice\\pyss\\test\\style.pyss", "r");
                if (input == NULL) {
                    error_exception(2);
                    return 2;
                }
                output = fopen("test\\out.css", "w");
                if (output == NULL) {
                    error_exception(3);
                    return 3;
                }
            #elif defined(__linux__)
                input = fopen("/mnt/c/code/Practice/pyss/test/style.pyss", "r");
                if (input == NULL) {
                    error_exception(2);
                    return 2;
                }
                output = fopen("test/out.css", "w");
                if (output == NULL) {
                    error_exception(3);
                    return 3;
                }
            #else
                #error pyss: unsupported operating system
            #endif
            break;
        
        case 2:
            input = fopen(argv[1], "r");
            if (input == NULL) {
                error_exception(2);
                return 2;
            }
            output = fopen("out.css", "w");
            if (output == NULL) {
                error_exception(3);
                return 3;
            }
            break;
    }

    
    input_curline = malloc(1001);
    while (fgets(input_curline, 1001, input) != NULL)
    {
        lex(input, input_curline);
        if (tokens[1][0] != '\0' && fatality == 0)
        {
            printf("[%i] ", tokens[0][0]);
            for (int i = 1; tokens[i][0] != '\0'; i++)
                printf("%s"BACKGROUND_BLACK" "RESET, tokens[i]);
            printf("\n");
        }
    }
    return 0;
}