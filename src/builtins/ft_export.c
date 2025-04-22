/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:16 by fmick             #+#    #+#             */
/*   Updated: 2025/04/22 18:40:10 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		tmp = ft_split_env(envp[i]);
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
	t_env	*cur;

	if (!str[1])
	{
		cur = mini->export_env;
		while (cur)
		{
			if (cur->value == NULL)
				printf("export %s\n", cur->key);
			else
				printf("export %s=\"%s\"\n", cur->key, cur->value);
			cur = cur->next;
		}
		return (0);
	}
	return (1);
}

static void	ft_export_no_value(t_mini *mini, char *key)
{
	t_env	*last;

	if (!ft_find_key(mini->export_env, key))
	{
		last = mini->export_env;
		while (last && last->next)
			last = last->next;
		if (last)
			last->next = ft_add_env_node(key, NULL);
		else
			mini->export_env = ft_add_env_node(key, NULL);
	}
}

void	ft_add_env_export(t_mini *mini, char *key, char *value)
{
	t_env	*export_node;
	t_env	*last;

	// Update or add in the main env
	if (ft_env_exists(mini->env, key, value) == 0)
	{
		last = mini->env;
		while (last && last->next)
			last = last->next;
		if (last)
			last->next = ft_add_env_node(key, value);
		else
			mini->env = ft_add_env_node(key, value);
	}
	// Now check if the key exists in export_env and update it
	export_node = mini->export_env;
	while (export_node)
	{
		if (ft_strcmp(export_node->key, key) == 0)
		{
			// Key found, update value
			free(export_node->value);
			export_node->value = ft_strdup(value);
			return ;
		}
		export_node = export_node->next;
	}
	// If not found, add it
	last = mini->export_env;
	while (last && last->next)
		last = last->next;
	if (last)
		last->next = ft_add_env_node(key, value);
	else
		mini->export_env = ft_add_env_node(key, value);
}

int	ft_export(t_mini *mini, char **str)
{
	int	i;

	if (!str[1])
		return (ft_export_env(mini, str));
	i = 1;
	while (str[i])
	{
		if (ft_strchr(str[i], '='))
		{
			if (ft_has_equal(mini, str[i]))
				mini->exit_status = 1;
		}
		else
		{
			if (!export_validity(str[i]))
				ft_error(mini, str, i, 1);
			else
				ft_export_no_value(mini, str[i]);
		}
		i++;
	}
	return (mini->exit_status);
}
