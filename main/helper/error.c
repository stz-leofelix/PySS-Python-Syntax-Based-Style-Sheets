#include <stdio.h>

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

// Helper function prototype
char *h_strnt_trunc(char *line);
int fatalerr_terminate(void);

// Global variable
int fatality = 0;

void perr(const char *line, int line_number, const char *err, int err_start, int err_end)
{
    char line_copy[1001];
    snprintf(line_copy, sizeof(line_copy), "%s", line);

    printf(BOLD RED"ParserError:\n"RESET);
    printf(BOLD CYAN"Line |\n"RESET);

    printf(BOLD CYAN"%4i | %s\n"RESET, line_number, h_strnt_trunc(line_copy));

    printf(BOLD CYAN"     | "RESET);
    for (int i = 0; i < err_start; i++)
    printf(" ");
    for (int i = err_start; i < err_end; i++)
    printf(BOLD RED"~"RESET);
    printf("\n");
    printf(BOLD CYAN"     | "RESET BOLD RED"%s"RESET, err);

    printf("\n\n");
    fatality = 1;
}

int main(void)
{
    perr("aply bg-blue-800 font-bold", 44, "Unknown keyword \"aply\". Did you mean \"apply\"?", 0, 4);
    perr("aply bg-blue-800 font-bold", 44, "Unknown keyword \"aply\". Did you mean \"apply\"?", 0, 4);
    perr("aply bg-blue-800 font-bold", 44, "Unknown keyword \"aply\". Did you mean \"apply\"?", 0, 4);
    if (fatalerr_terminate())
    return fatality;
    return 0;
}

char *h_strnt_trunc(char *line)
{
    char *rtrnstr = line;
    int i = 0;
    for (; rtrnstr[i] != '\n' && rtrnstr[i] != '\0'; i++){}
    rtrnstr[i] = '\0';
    return rtrnstr;
}

int fatalerr_terminate(void)
{
    if (fatality != 0)
    {
        printf(BOLD RED"Fatal Error(s) emitted. Compilation terminated.\n"RESET);
        return 1;
    }
    else
    {
        return 0;
    }
}