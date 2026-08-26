#include <stdlib.h>
#include <string.h>
#include "data.h"

// Helper function prototype
char* strip(char *string);

// Lexer function that returns tokens in an array of strings (array of chars)
void lex(char *tokens[], FILE *input)
{
    // Initialize variables
    char *strbuffer = malloc(1001);
    int loopcounter = 0;
    int strcounter = 0;
    int charcounter = 0;
    // Repeat reading each lines of the input until it reaches the end of the file
    while (fgets(strbuffer, 1001, input) != NULL)
    {
        // Strip away uncessary whitespaces
        strbuffer = strip(strbuffer);

        // Repeat until the current chracter from the read line is a null terminator
        while (strbuffer[loopcounter] != '\0')
        {
            // If the current character is a valid character
            if (strbuffer[loopcounter] != ' ' && strbuffer[loopcounter] != '\t')
            {   
                tokens[strcounter][charcounter] = strbuffer[loopcounter];
                tokens[strcounter][charcounter + 1] = '\0';
                charcounter++;
                loopcounter++;
            }
            // If the current character is a tab
            else if (strbuffer[loopcounter] == '\t')
            {
                tokens[strcounter][charcounter] = '\t';
                tokens[strcounter][charcounter + 1] = '\0';
                charcounter = 0;
                loopcounter++;
                strcounter++;
            }
            // If the current character is a space
            else if (strbuffer[loopcounter] == ' ')
            {
                strcounter++;
                charcounter = 0;
                loopcounter++;
            }
        }
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
    char lastout = 'c';
    char* output = malloc(1001);

    // Loop through the entire given string
    for (int i = 0; string[i] != '\0'; i++)
    {
        // Detects valid characteres
        if (string[i] != ' ')
        {
            output[appendcounter] = string[i];
            output[appendcounter + 1] = '\0';
            charcounter++;
            appendcounter++;
            spacecounter = 0;
            lastout = string[i];
        }
        // Detects non trailing whitespace
        else if (string[i] == ' ' && spacecounter < 1)
        {
            output[appendcounter] = string[i];
            output[appendcounter + 1] = '\0';
            appendcounter++;
            spacecounter++;
            lastout = string[i];
        }
    }

    // Checks if the last character is a space
    if (lastout == ' ')
    {
        output[appendcounter - 1] = '\0';
    }
    return output;
}