#include "minishell.h"

int ft_exit(t_mini *mini, char **args)
{
    int exit_status;

    if (args[1] == NULL)
    {
        exit_status = mini->exit_status;
    }
    else
    {
        exit_status = ft_atoi(args[1]);
        if (exit_status < 0 || exit_status > 255)
        {
            ft_putstr_fd("exit: exit status out of range\n", STDERR_FILENO);
            return 1;
        }
    }
    
    free_all_resources(mini); // Function to free all allocated resources
    exit(exit_status);
}