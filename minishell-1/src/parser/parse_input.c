#include "minishell.h"

char **parse_input(char *input)
{
    char **tokens;
    // Tokenization logic will go here
    // For now, we will just return NULL
    return NULL;
}

void free_tokens(char **tokens)
{
    int i = 0;
    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

int is_valid_input(char *input)
{
    // Input validation logic will go here
    // For now, we will just return 1 (valid)
    return 1;
}