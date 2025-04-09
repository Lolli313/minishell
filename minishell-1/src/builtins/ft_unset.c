#include "minishell.h"

int ft_unset(t_env **env, char **str)
{
    int i;
    t_env *current;
    t_env *prev;

    i = 1;
    while (str[i])
    {
        current = *env;
        prev = NULL;
        while (current)
        {
            if (ft_strcmp(current->key, str[i]) == 0)
            {
                if (prev)
                    prev->next = current->next;
                else
                    *env = current->next;
                free(current->key);
                free(current->value);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
    return (0);
}