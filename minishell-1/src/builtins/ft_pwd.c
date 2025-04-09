#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int ft_pwd(void)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        return 0;
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }
}