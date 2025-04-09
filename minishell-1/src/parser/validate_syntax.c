#include "minishell.h"

int validate_syntax(char *input)
{
    int i;
    int parentheses;

    i = 0;
    parentheses = 0;

    while (input[i])
    {
        if (input[i] == '(')
            parentheses++;
        else if (input[i] == ')')
            parentheses--;
        
        if (parentheses < 0)
            return (0); // Unmatched closing parenthesis

        i++;
    }

    return (parentheses == 0); // Return 1 if matched, 0 otherwise
}

int check_for_unexpected_tokens(char *input)
{
    // Implement logic to check for unexpected tokens in the input
    // For example, check for consecutive operators or invalid characters
    return 1; // Placeholder return value
}

int validate_command(char *command)
{
    if (!validate_syntax(command))
        return (0); // Invalid syntax

    if (!check_for_unexpected_tokens(command))
        return (0); // Unexpected tokens found

    return (1); // Command is valid
}