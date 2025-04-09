#include "minishell.h"

static int is_delimiter(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '<' || c == '>');
}

static int is_quote(char c)
{
    return (c == '"' || c == '\'');
}

static int count_tokens(char *input)
{
    int count = 0;
    int in_quotes = 0;

    while (*input)
    {
        if (is_quote(*input))
            in_quotes = !in_quotes;
        if (!is_delimiter(*input) && !in_quotes)
        {
            count++;
            while (*input && !is_delimiter(*input))
                input++;
        }
        else
        {
            input++;
        }
    }
    return count;
}

char **tokenize_input(char *input)
{
    char **tokens;
    int i = 0;
    int j = 0;
    int token_len = 0;
    int in_quotes = 0;

    int token_count = count_tokens(input);
    tokens = malloc(sizeof(char *) * (token_count + 1));
    if (!tokens)
        return NULL;

    while (*input)
    {
        if (is_quote(*input))
            in_quotes = !in_quotes;
        if (!is_delimiter(*input) || in_quotes)
        {
            token_len = 0;
            while (*input && (!is_delimiter(*input) || in_quotes))
            {
                token_len++;
                input++;
            }
            tokens[j] = malloc(token_len + 1);
            if (!tokens[j])
                return NULL; // Handle memory allocation failure
            strncpy(tokens[j], input - token_len, token_len);
            tokens[j][token_len] = '\0';
            j++;
        }
        else
        {
            input++;
        }
    }
    tokens[j] = NULL;
    return tokens;
}