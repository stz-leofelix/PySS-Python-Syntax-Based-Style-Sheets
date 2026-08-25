#include <stdlib.h>
#include <string.h>
#include "data.h"

// Helper function prototypes
void parse_selector(void);
void parse_property(void);

// Parser function that reads the token given by lexer function and assign the values to a node accordinigly
void parse(char *tokens[])
{
    if (strcmp(tokens[0], "def") == 0)
    {
        parse_selector();
    }
    else if (strcmp(tokens[0], "\t") == 0)
    {
        parse_property();
    }
    return;
}

// Helper function parse selector
void parse_selector(void)
{
    node.type = "selector";

    for (int i = 1; tokens[i] != NULL; i++)
    {
        strcpy(node.name, tokens[i]);
    }
    return;
}

// Helper function parse property
void parse_property(void)
{
    node.type = "property";
    node.ident = 1;

    int value_count = 0;

    for (int i = 1; tokens[i] != NULL; i++)
    {
        if (strcmp(tokens[i], "\t"))
            node.ident++;
        else if (strcmp(tokens[i], "\t") != 0)
        {
            node.name = tokens[i];
            value_count = i;
            break;
        }
    }

    for (int i = 1; tokens[i + value_count] != NULL; i++)
        strcpy(node.value, tokens[i + value_count]);
    return;
}