// filepath: /minishell/src/builtins/ft_export.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:16 by fmick             #+#    #+#             */
/*   Updated: 2025/04/09 07:59:03 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_exists(t_env *env, char *key, char *value)
{
	t_env	*lst;

	lst = env;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			if (ft_strcmp(lst->value, value) != 0)
			{
				free(lst->value);
				lst->value = ft_strdup(value);
				return (1);
			}
			return (0);
		}
		lst = lst->next;
	}
	return (0);
}

t_env	*ft_init_export_env_(char **envp)
{
	char	**tmp;
	int		i;
	t_env	*last;
	t_env	*export_env;

	i = 0;
	export_env = NULL;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		if (!tmp)
			return (NULL);
		if (export_env == NULL)
			export_env = ft_add_env_node(tmp[0], tmp[1]);
		else
		{
			last = export_env;
			while (last->next)
				last = last->next;
			last->next = ft_add_env_node(tmp[0], tmp[1]);
		}
		free_matrix(tmp);
		i++;
	}
	return (export_env);
}

int	ft_export_env(t_mini *mini, char **str)
{
	if (!str[1]) 
	{
		t_env *cur = mini->export_env;
		while (cur)
		{
			printf("export %s", cur->key);
			if (cur->value && cur->value[0] != '\0')
				printf("=\"%s\"", cur->value);
			printf("\n");
			cur = cur->next;
		}
		return (0);
	}
	return (1);
}

int	ft_export(t_env *env, char **str)
{
	char	**temp;
	t_env	*last;
	int		i;
	char	*value;

	i = 1;
	while (str[i])
	{
		if (strchr(str[i], '=') == NULL)
		{

		}
		temp = ft_split(str[i], '=');
		if (!temp[0] || !export_validity(temp[0]))
			ft_putstr_fd(str[i], STDERR_FILENO);
		else
		{
			if (temp[1])
				value = temp[1];
			else
				value = "";
			if (ft_env_exists(env, temp[0], value) == 0)
			{
				last = env;
				while (last->next)
					last = last->next;
				last->next = ft_add_env_node(temp[0], value);
			}
			free_matrix(temp);
			i++;
		}
	}
	return (0);
}