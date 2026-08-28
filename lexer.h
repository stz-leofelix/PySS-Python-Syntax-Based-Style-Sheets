#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
    if (line[0] == '\n')
    {
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

    // Modify variables for next use
    strcounter++;
    loopcounter = 0;
    charcounter = 0;
    return;
}

// Helper lexer function that strips away uncessary whitespaces
char* strip(char *string)
{
    // Initialize variables
    int spacecounter = 0;
    int appendcounter = 0;
    int charcounter = 0;
    char* output = malloc(MAXCHAR);

    // Loop through the entire given string
    for (int i = 0; string[i] != '\0'; i++)
    {
        // Detects newline and return cartilage
        if (string[i] == '\n' || string[i] == '\r')
        {
            continue;
        }
        // Detects valid characteres
        else if (string[i] != ' ')
        {
            output[appendcounter] = string[i];
            output[appendcounter + 1] = '\0';
            charcounter++;
            appendcounter++;
            spacecounter = 0;
        }
        // Detects non trailing whitespace
        else if (string[i] == ' ' && spacecounter < 1)
        {
            output[appendcounter] = string[i];
            output[appendcounter + 1] = '\0';
            appendcounter++;
            spacecounter++;
        }
    }

    // Checks if the last character is a space
    if (output[appendcounter] == ' ')
        output[appendcounter] = '\0';
    // Checks if the first character is a space
    if (output[0] == ' ')
        strcpy(output, &output[1]);
    return output;
}