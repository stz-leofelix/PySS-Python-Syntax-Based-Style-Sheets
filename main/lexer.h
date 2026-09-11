#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "data.h"

// Program Macros
#define MAXCHAR 1001

// Helper function prototype
char *strip(char *string, int *rawindex);

// Lexer function that populate the tokens according to the line given.
void lex(FILE *input, char *line)
{
    // Initialize variables
    char *rawline = malloc(strlen(line) + 1); strcpy(rawline, line);
    int rawindex = 0;
    int *rawindex_ptr = &rawindex;
    int index = 1;
    int character = 0;
    int indent = 0;
    int line_index = 0;

    // Checks if the given line is empty, populate the first token index 0 to \0 if so
    if (line[0] == '\n' || line[0] == '\r')
    {
        tokens[0][0] = '\0';
        free(rawline);
        return;
    }

    // Strips away uncessary whitespaces(non indentation) from line before processing
    char *stripped = strip(line, rawindex_ptr);
    if (stripped == NULL)
    {
        free(stripped);
        free(rawline);
        return;
    }
    strcpy(line, stripped);
    free(stripped);

    // Processing the indentation
    for (; line[line_index] == ' '; line_index++)
    {
        if ((line_index % 4) == 0)
        indent++;
    }
    tokens[0][0] = (char) indent; tokens[0][1] = '\0';

    // Loop through each characters in given line
    for (int i = line_index; line[i] != '\0'; i++)
    {
        // Append string literals
        if (line[i] == '"' || line[i] == '\'')
        {
            char quote = line[i]; i++;
            tokens[index][character] = quote; tokens[index][character + 1] = '\0'; character++;
            for (; line[i] != quote; i++)
            {
                tokens[index][character] = line[i]; tokens[index][character + 1] = '\0'; character++;
            }
            tokens[index][character] = quote; tokens[index][character + 1] = '\0'; index++; character++;
        }
        // Append valid characters
        else if (line[i] != ' ')
        {
            tokens[index][character] = line[i]; tokens[index][character + 1] = '\0';
            character++;
        }
        // Advance index if character is space
        else if (line[i] == ' ')
        {
            index++;
            character = 0;
        }
    }

    // Null terminate the token next to the last written token
    tokens[index + 1][0] = '\0';
    return;
}

// Helper lexer function that strips away uncessary whitespaces
char *strip(char *string, int *rawindex)
{
    // Initialize variable
    char *output = malloc(MAXCHAR);
    if (output == NULL)
    return NULL;
    int character = 0;
    int space = 0;
    int append = 0;

    // Loop through string & append non excess characters (not multiple spaces etc)
    for (int i = 0; string[i] != '\0'; i++, (*rawindex)++)
    {
        // Ignore linefeed \n and carriage return \r
        if (string[i] == '\n' || string[i] == '\r')
        {
            continue;
        }
        // Detects string literals
        else if (string[i] == '"' || string[i] == '\'')
        {
            char quote = string[i];
            output[append] = quote; output[append + 1] = '\0'; append++; i++;
            for (; string[i] != quote; i++)
            {
                output[append] = string[i]; output[append + 1] = '\0'; append++;
            }
            output[append] = quote; output[append + 1] = '\0';  append++;
        }
        // Detects indentation
        else if (string[i] == ' ' && character == 0)
        {
            // Appends space
            output[append] = ' '; output[append + 1] = '\0';    
            append++;
        }
        // Detects non-whitespace character
        else if (string[i] != ' ')
        {
            output[append] = string[i]; output[append + 1] = '\0';
            character++;
            append++;
            space = 0;
        }
        // Detects non trailing whitespace character
        else if (string[i] == ' ' && space < 1)
        {
            output[append] = ' '; output[append + 1] = '\0';
            append++;
            space++;
        }
    }

    // Strip out the last remaning space if there is a space at the last char
    if (output[append - 1] == ' ')
        output[append - 1] = '\0';

    return output;
}