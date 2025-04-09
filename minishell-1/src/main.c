#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_mini mini;

    (void)argc;
    (void)argv;

    mini.export_env = ft_init_export_env_(envp);
    if (!mini.export_env)
    {
        fprintf(stderr, "Failed to initialize environment.\n");
        return EXIT_FAILURE;
    }

    // Main shell loop
    while (1)
    {
        char *input = readline("minishell> ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (*input)
        {
            add_history(input);
            // Parse and execute the input command
            // (Implementation of parsing and execution is not shown here)
        }
        free(input);
    }

    // Free environment variables and other resources
    // (Implementation of cleanup is not shown here)

    return EXIT_SUCCESS;
}