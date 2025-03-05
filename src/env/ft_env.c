/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:36:50 by fmick             #+#    #+#             */
/*   Updated: 2025/03/05 09:00:43 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. size_t ft _env_size (lst size)
// 2. add envp to list
// 3. ft_init_env

// added + 1 ---> see keylen & valuelen
/*static int	ft_envlen(char *str)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		i++;
		count++;
	}
	return (count + 1);
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
}*/

// convert a linked list of environments into a single string
void	ft_env_display(t_env *env)
{
	t_env	*temp;
	char	*tmp;
	
	temp = env;
	while (temp)
	{
		if (temp->key && temp->value)
		{
			//ft_strjoin(temp->key, temp->key);
			tmp = ft_strjoin(temp->key, "=");
			tmp = ft_strjoin(tmp, temp->value);
			tmp = ft_strjoin(tmp, "\n");
		}
		printf("%s", tmp);
		temp = temp->next;
	}
}

t_env	*ft_add_env_node(char **array)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = array[0];
	env->value = array[1];
	env->next = NULL;
	return (env);
}

t_env	*ft_init_env(char **envp)
{
	char	**temp;
	t_env	*env;
	int		i;
	t_env	*last;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		if (env == NULL)
			env = ft_add_env_node(temp);
		else
		{
			last = env;
			while (last->next)
				last = last->next;
			last->next = ft_add_env_node(temp);
		}
		i++;
	}
	ft_env_display(env);
	return (env);
}
// char **envp
// getenv("USER")
// USER=NAME
