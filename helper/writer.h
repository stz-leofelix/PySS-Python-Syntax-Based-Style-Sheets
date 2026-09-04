#include <string.h>
#include <stdio.h>
#include "data.h"

// Writer function that looks at node and fprintf accordingly
void write(FILE *output)
{
    if (strcmp(node.type, "selector") == 0)
    {
        fprintf(output, "%s \{\n", node.name);
    }
    else if (strcmp(node.type, "property") == 0)
    {
        for (int i = 0; i < node.indent; i++)
            fprintf(output, "\t");
        fprintf(output, "%s %s;\n", node.name, node.value);
    }
}