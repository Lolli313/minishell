#include "minishell.h"

void handle_error(const char *message)
{
    perror(message);
}

void handle_memory_error(void)
{
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
}

void handle_command_error(const char *command)
{
    fprintf(stderr, "Command not found: %s\n", command);
}

void handle_syntax_error(const char *message)
{
    fprintf(stderr, "Syntax error: %s\n", message);
}