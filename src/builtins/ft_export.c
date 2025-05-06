/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:16 by fmick             #+#    #+#             */
/*   Updated: 2025/05/06 11:06:24 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_init_export_env_(char **envp)
{
	char	**tmp;
	int		i;
	t_env	*last;
	t_env	*export_env;

	i = -1;
	export_env = NULL;
	while (envp[++i])
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

static void	ft_sort_env(t_env **env)
{
    t_env	*current;
    t_env	*next;
    char	*temp_key;
    char	*temp_value;

    if (!env || !*env)
        return ;
    current = *env;
    while (current)
    {
        next = current->next;
        while (next)
        {
            if (ft_strcmp(current->key, next->key) > 0)
            {
                // Swap keys
                temp_key = current->key;
                current->key = next->key;
                next->key = temp_key;
                // Swap values
                temp_value = current->value;
                current->value = next->value;
                next->value = temp_value;
            }
            next = next->next;
        }
        current = current->next;
    }
}

int	ft_has_equal(t_mini *mini, char *str)
{
	char	**temp;
	char	*value;

	temp = ft_split_env(str);
	if (!temp[0] || !export_validity(temp[0]))
	{
		ft_putstr_fd("minishell: export: `", STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd("': not a valid identifier\n", STDERR);
		free_matrix(temp);
		return (1);
	}
	else
	{
		if (temp[1])
			value = temp[1];
		else
			value = "";
		update_or_add_env(&(mini->env), temp[0], value);
		ft_sort_env(&(mini->env));
		update_or_add_env(&(mini->export_env), temp[0], value);
	}
	free_matrix(temp);
	return (0);
}

static void	ft_export_no_value(t_mini *mini, char *key)
{
	t_env	*curr;
	t_env	*last;

	curr = mini->export_env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return ;
		curr = curr->next;
	}
	if (mini->export_env)
	{
		last = mini->export_env;
		while (last->next)
			last = last->next;
		last->next = ft_add_env_node(key, NULL);
	}
	else
		mini->export_env = ft_add_env_node(key, NULL);
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
