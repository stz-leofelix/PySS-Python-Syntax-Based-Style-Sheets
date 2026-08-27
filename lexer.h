#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data.h"

// Program Macros
#define MAXCHAR 1001

// Helper function prototype
char* strip(char *string);

// Lexer function that returns tokens in an array of strings (array of chars)
void lex(FILE *input)
{
    // Initialize variables
    char *strbuffer = malloc(MAXCHAR);
    int loopcounter = 0;
    int strcounter = 0;
    int charcounter = 0;

    // Repeat reading each lines of the input until it reaches the end of the file
    while (fgets(strbuffer, MAXCHAR, input) != NULL)
    {
        // Strip away uncessary whitespaces
        char *stripped_text = strip(strbuffer);
        strcpy(strbuffer, stripped_text);
        free(stripped_text);

        // Repeat until the current chracter from the read line is a null terminator
        while (strbuffer[loopcounter] != '\0')
        {
            // If the current character is a valid character
            if (strbuffer[loopcounter] != ' ')
            {   
                tokens[strcounter][charcounter] = strbuffer[loopcounter];
                tokens[strcounter][charcounter + 1] = '\0';
                charcounter++;
                // If the character is a a tab, to left characters
                if (strbuffer[loopcounter] == '\t')
                {
                    charcounter = 0;
                    strcounter++;
                }
                loopcounter++;
            }
            // If the current character is a space
            else if (strbuffer[loopcounter] == ' ')
            {
                strcounter++;
                charcounter = 0;
                loopcounter++;
            }
        }
        strcounter++;
        loopcounter = 0;
        charcounter = 0;
    }
    free(strbuffer);
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
    if (output[appendcounter - 1] == ' ')
        output[appendcounter] = '\0';
    // Checks if the first character is a space
    if (output[0] == ' ')
        output[0] = output[1];
    return output;
}