#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "data.h"

// Program Macros
#define MAXCHAR 1001

// Helper function prototype
char* strip(char *string);

// Lexer function that populate the tokens according to the line given.
void lex(FILE *input, char *line)
{
    // Initialize variables
    int loopcounter = 0;
    int strcounter = 0;
    int charcounter = 0;

    // If the line is empty
    if (line[0] == '\n' || line[0] == '\r')
    {
        tokens[0][0] = '\0';
        return;
    }

    // Strip away uncessary whitespaces
    char *stripped_text = strip(line);
    strcpy(line, stripped_text) ;
    free(stripped_text);

    // Repeat until the current chracter from the read line is a null terminator
    while (line[loopcounter] != '\0')
    {
        // If the current character is a valid character
        if (line[loopcounter] != ' ')
        {   
            tokens[strcounter][charcounter] = line[loopcounter];
            tokens[strcounter][charcounter + 1] = '\0';
            charcounter++;
            // If the character is a a tab, to left characters
            if (line[loopcounter] == '\t')
            {
                charcounter = 0;
                strcounter++;
            }
            loopcounter++;
        }
        // If the current character is a space
        else if (line[loopcounter] == ' ')
        {
            strcounter++;
            charcounter = 0;
            loopcounter++;
        }
    }
    // Add the null terminator next to the last token
    tokens[strcounter][charcounter] = '\0';
    // Null terminate the last written string.
    tokens[strcounter + 1][0] = '\0';

    // Modify variables for next use
    strcounter++;
    loopcounter = 0;
    charcounter = 0;
    return;
}

// REWRITING LEX (SUBLEX)
void sublex(FILE *input, char *line)
{
    // Initialize variables
    int index = 1;
    int character = 0;
    int indent = 0;

    // Checks if the given line is empty, populate the first token index 0 to \0 if so
    if (line[0] == '\n' || line[0] == '\r')
    {
        tokens[0][0] = '\0';
        return;
    }

    // Strips away uncessary things from line before processing
    char *stripped = strip(line);
    strcpy(line, stripped);
    free(stripped);

    // Processing the indentation
    for (int i = 0; line[i] == ' '; i++)
    {
        if ((i % 4) == 0)
        indent++;
    }
    tokens[0][0] = (char) indent; tokens[0][1] = '\0';

    // Loop through each characters in given line
    for (int i = character; line[i] != '\0'; i++)
    {
        // Append valid characters
        if (line[i] != ' ')
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
char* strip(char *string)
{
    // Initialize variable
    char *output = malloc(MAXCHAR);
    int character = 0;
    int space = 0;
    int append = 0;

    // Loop through string & append non excess characters (not multiple spaces etc)
    for (int i = 0; string[i] != '\0'; i++)
    {
        // Ignore linefeed \n and carriage return \r
        if (string[i] == '\n' || string[i] == '\r')
        {
            continue;
        }
        // Detects and include identation
        else if (string[i] == ' ' && character == 0)
        {
            // Appends space
            output[append] = ' '; output[append + 1] = '\0';    
            append++;
        }
        // Detects and include non-whitespace character
        else if (string[i] != ' ')
        {
            output[append] = string[i]; output[append + 1] = '\0';
            character++;
            append++;
            space = 0;
        }
        // Detects and include non trailing whitespace character
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