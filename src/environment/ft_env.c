/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:36:50 by fmick             #+#    #+#             */
/*   Updated: 2025/03/04 13:34:32 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. size_t ft _env_size (lst size)
// 2. add envp to list
// 3. ft_init_env

// added + 1 ---> see keylen & valuelen
static int	ft_envlen(char *str)
{
	size_t	i;
	int		count;

	i = 0;
	while (str[i])
	{
		i++;
		count++;
	}
	return (count + 1);
}

static char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

size_t	ft_env_lst_size(t_env *lst)
{
	size_t	lst_size;

	lst_size = 0;
	while (lst && lst->next != NULL)
	{
		lst = lst->next;
		lst_size++;
	}
	return (lst_size);
}
// keylen + valuelen + 2 (= and \n)
size_t	ft_env_value_size(t_env *lst)
{
	size_t	key_len;
	size_t	value_len;

	value_len = 0;
	key_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->key && lst->value != NULL)
		{
			key_len += ft_envlen(lst->key); // + 1 added in ft_envlen for = sign
			value_len += ft_envlen(lst->value); // + 1 added in ft_envlen for \n
		}
		lst = lst->next;
	}
	return (key_len + value_len); // ex NAME=fmick = 4 + 1 + 5 + 1 = 11;
}

// convert a linked list of environments into a single string
char	*ft_env_display(t_env *lst)
{
	char	*env;

	env = malloc(sizeof(char) * (ft_env_value_size(lst) + 1));
	if (!env)
	{
		return (NULL);
		printf(R "DB: Malloc failed (env_display)" RESET);
	}
	while (lst)
	{
		if (lst->key && lst->value)
		{
			ft_strcat(env, lst->key);
			ft_strcat(env, "=");
			ft_strcat(env, lst->value);
			ft_strcat(env, "\n");
		}
		lst = lst->next;
	}
	return (env);
}

int	ft_init_env(t_mini *mini, char *array)
{
	t_env	*env;
    t_env   *cur;
    char    **key_value;
	size_t	i;

    i = 0;
    mini->env_lst = NULL;
    while (array[i])
    {
        env = malloc(sizeof(t_env));
        if (!env)
            {
                return NULL;
                printf(R "DB: Malloc failed (init_env)" RESET);
            }
        key_value = ft_split(array[i], '=');
        if (!key_value)
        {
            printf(R "DB: Split failed (init_env)" RESET);
            return -1;
        }
        env->key = key_value[0];
        env->value = key_value[1];
        env->next = NULL;
        if (mini->env_lst == NULL)
        {
            mini->env_lst = env;
        }
        else
        {
            cur = mini->env_lst;
            while (cur->next)
            {
                cur = cur->next;
            }
        }
        free(key_value);
        i++;
    }
}
