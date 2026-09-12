#include <stdio.h>
#include <string.h>
#include "data.h"

#ifndef ANSI_COLORS_H
#define ANSI_COLORS_H

#define RESET   "\x1b[0m"

#define BLACK   "\x1b[30m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"

#define BOLD    "\x1b[1m"
#define DIM     "\x1b[2m"

#define PRINT_COLOR(color, text) color text RESET

#endif

int fatality = 0;

// Error Functions
void error_exception(int code);
void error_lexer(int code);

// Helper Functions
int dprintln(char *line, unsigned int line_number, unsigned int column_start, unsigned int column_end)
{
    // Adjust line padding
    int line_digit = snprintf(NULL, 0, "%d", line_number);
    unsigned int line_indent = (line_digit < 4) ? 4 : line_digit;

    // Print line header
    printf(
        BOLD CYAN"%-*s |\n"
        "%*i | "RESET"%.*s"BOLD CYAN"%.*s\n"
        "%*c  |"RED,
        line_indent, "Line", line_indent, line_number, column_start - 1, line, column_end - (column_start - 1), line + column_start, line_indent, NULL
    );

    for (int i = 0; i < column_start; i++)
    putchar(' ');
    for (int i = column_start; i <= column_end; i++)
    putchar('~');
    printf(RESET);

    printf(BOLD CYAN"\n%*c  | "RESET, line_indent, NULL);
    return line_indent;
}

int main(void)
{
    error_lexer(1);
}

void error_exception(int code)
{
    // Print "ExceptionError" Start
    printf(BOLD RED"ExceptionError: "RESET);

    switch (code) {
        case 0:
            printf("An unknown error has occured.\n");
            fatality = 1;
            break;
        
        case 1:
            printf("Read error occured, unable to read from specified file.\n");
            fatality = 1;
            break;
        
        case 2:
            printf("Write error occured, unable to write to specified file.\n");
            fatality = 1;
            break;
    }
}

void error_lexer(int code)
{
    // Print Error "LexerError: " filename:line:column
    printf(BOLD RED"LexerError: "RESET"%s:%i:%i\n", "pyss.c", 123, 9);

    switch (code) {
        case 0:
            dprintln("content: \"literally", 100000000000, 18, 18);
            printf(BOLD RED"Unknown LexerError occoured. "RESET"The last character read is given above.\n");
            fatality = 1;
            break;

        case 1:
            dprintln("content: \"litearlly", 123, 9, 18);
            printf(BOLD RED"Expected closing quote for string, "RESET"Perhaps Did you forget a "BOLD GREEN"' "RESET"or "BOLD GREEN"\""RESET" ?\n");
            fatality = 1;
            break;
    }
}