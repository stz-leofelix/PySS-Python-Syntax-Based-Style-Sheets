#include "main/data.h"
#include "main/lexer.h"
#include "main/parser.h"
#include "main/writer.h"
#include "main/error.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    error_lexer(1);

    // input = fopen("C:\\code\\Practice\\pyss\\test\\style.pyss", "r");
    // output = fopen("test\\out.css", "w");
    // input_current_line = malloc(1001);
    // while (fgets(input_current_line, 1001, input) != NULL)
    // {
    //     lex(input, input_current_line);
    //     if (tokens[0][0] != '\0')
    //     {
    //         printf("[%i] ", tokens[0][0]);
    //         for (int i = 1; tokens[i][0] != '\0'; i++) {
    //             printf("[%s] ", tokens[i]);
    //         }
    //         printf("\n");
    //     }
    // }
    // return 0;
}