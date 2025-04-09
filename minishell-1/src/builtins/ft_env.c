#include "minishell.h"

int ft_env(t_mini *mini)
{
    t_env *cur = mini->export_env;

    while (cur)
    {
        printf("%s=%s\n", cur->key, cur->value ? cur->value : "");
        cur = cur->next;
    }
    return 0;
}