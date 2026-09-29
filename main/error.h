#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"

#ifndef ERRORFUNC_IMP
#define ERRORFUNC_IMP

#define RESET   "\x1b[0m"

#define BLACK   "\x1b[30m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"

#define BACKGROUND(color) BACKGROUND_##color
#define BACKGROUND_BLACK   "\x1b[40m"
#define BACKGROUND_RED     "\x1b[41m"
#define BACKGROUND_GREEN   "\x1b[42m"
#define BACKGROUND_YELLOW  "\x1b[43m"
#define BACKGROUND_BLUE    "\x1b[44m"
#define BACKGROUND_MAGENTA "\x1b[45m"
#define BACKGROUND_CYAN    "\x1b[46m"
#define BACKGROUND_WHITE   "\x1b[47m"

#define BOLD    "\x1b[1m"
#define DIM     "\x1b[2m"

#define PRINT_COLOR(color, text) color text RESET

// Function prototypes
char *strnl_trunc(char *line);
int strlspc(char *line);

int fatality = 0;

// Error Functions
void error_exception(int code);
// void error_lexer(int code);

// Printing flavoured message function
void dprintn(int type, int indent)
{
    switch (type) {
        case 0:
            fprintf(stderr, BOLD CYAN"%*c │ "RESET, indent, ' ');
            break;
        
        case 1:
            fprintf(stderr, BOLD BLUE"%*s │ "RESET, indent, "Note");
            break;
        
        case 2:
            fprintf(stderr, BOLD GREEN"%*s │ "RESET, indent, "Tip");
            break;

        case 3:
            fprintf(stderr, BOLD YELLOW"%*s │ "RESET, indent, "Caution");
            break;
    }
}
// Printing line function
int dprintln(char *line, unsigned int line_number, unsigned int column_start, unsigned int column_end)
{
    // Processing indentation and copying line
    int indent = strlspc(line);
    char *lncpy = strnl_trunc(line);
    if (lncpy == NULL) {
        return 0;
    }
    column_start -= indent;
    column_end -= indent;
    lncpy += indent;

    // Adjust line padding
    int line_digit = snprintf(NULL, 0, "%d", line_number);
    unsigned int line_indent = (line_digit < 4) ? 4 : line_digit;

    // Underline, error highlighting
    char *underline = malloc(strlen(line) + 1);
    if (underline == NULL) {
        free(lncpy);
        error_exception(1);
        return 0;
    }
    for (int i = 0; i < column_start; i++)
    underline[i] = ' ';
    for (int i = column_start; i <= column_end; i++) {
    underline[i] = '~'; underline[i + 1] = '\0'; }
   
    // Print line header
    fprintf(stderr,
        BOLD BLUE"%*s │\n"
        "%*i │ "RESET,
        line_indent, "Line", 
        line_indent, line_number
    );
    // Loop to print highlighted line
    for (int i = 0; lncpy[i] != '\0'; i++) {
        // If iteration is outside of errorcolumn scope
        if (i < column_start || i > column_end) {
            fprintf(stderr,
                RESET"%c", lncpy[i]
            );
        }
        // If iteration is inside of errorcolumn scope
        else if (i >= column_start && i <= column_end) {
            fprintf(stderr,
                BOLD BLUE"%c", lncpy[i]
            );
        }
    }
    // Print line footer
    fprintf(stderr,
        BOLD BLUE"\n%*c │ "RED"%s\n"
        BOLD BLUE"%*c │ "RESET,
        line_indent, ' ', underline,
        line_indent, ' '
    );

    free(underline);
    return line_indent;
}
// Truncating \n from string function
char *strnl_trunc(char *line)
{
    // Allocate and copy line to truncline
    char *truncline = malloc(strlen(line) + 1);
    if (truncline == NULL) {
        error_exception(1);
        return NULL;
    }
    strcpy(truncline, line);

    // Find the line feed and null terminator
    int i = 0;
    for (; truncline[i] != '\0' && truncline[i] != '\n' && truncline[i] != '\r'; i++) {}

    // Nulltermminate string at given null terminator or at newline
    // Cut string's newline to null terminate if exist
    truncline[i] = '\0';
    return truncline;
}
// Truncating indentation & spaces from start of the string function
int strlspc(char *line)
{
    // Create a copy of line
    char *lncpy = malloc(strlen(line) + 1);
    if (lncpy == NULL) {
        error_exception(1);
        return 0;
    }
    strcpy(lncpy, line);

    int space = 0;
    for (; lncpy[space] == ' '; space++) {}
    lncpy += space;
    return space;
}

void error_exception(int code)
{
    // Print "ExceptionError" Start
    fprintf(stderr, BOLD RED"ExceptionError: "RESET);

    switch (code) {
        case 0:
            fprintf(stderr, "An unknown error has occured.\n");
            fatality = 1;
            break;
        
        case 1:
            fprintf(stderr, "Unable to allocate memory for required task.\n");
            fatality = 1;
            break;

        case 2:
            fprintf(stderr, "Read error occured, unable to read from specified file.\n");
            fatality = 1;
            break;
        
        case 3:
            fprintf(stderr, "Write error occured, unable to write to specified file.\n");
            fatality = 1;
            break;
    }
}

void error_lexer(int code)
{
    // Print Error "LexerError: " filename:line:column
    fprintf(stderr, BOLD RED"LexerError: "RESET"%s:%i:%i\n", "style.pyss", dlexer_dlinenum, dlexer_dcolumn + 1);

    switch (code) {
        case 0:
            dprintln(dlexer_line, dlexer_linenum, dlexer_column, dlexer_column);
            fprintf(stderr, BOLD RED"Unknown LexerError occoured. "RESET"The last character read is given above.\n");
            fatality = 1;
            break;

        case 1:
            unsigned int indent = dprintln(dlexer_dline, dlexer_dlinenum, dlexer_dcolumn, dlexer_dcolumnend);
            char quote = dlexer_dline[dlexer_dcolumn];
            fprintf(stderr, BOLD RED"Expected closing quote for string. \n"RESET);
            dprintn(2, indent);
            fprintf(stderr, RESET"Perhaps did you forget a "BOLD GREEN"%c"RESET" ?\n", quote);
            fatality = 1;
            break;
    }
}

#endif
