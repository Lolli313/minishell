#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int ft_cd(char **args, t_mini *mini)
{
    char *path;

    if (!args[1])
    {
        path = getenv("HOME");
        if (!path)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
    }
    else
    {
        path = args[1];
    }

    if (chdir(path) != 0)
    {
        perror("cd");
        return 1;
    }

    // Update the current working directory in the environment
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        ft_setenv("PWD", cwd, mini);
    }
    return 0;
}