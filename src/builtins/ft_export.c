/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:16 by fmick             #+#    #+#             */
/*   Updated: 2025/04/14 11:05:28 by fmick            ###   ########.fr       */
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
			if (cur->value == NULL || cur->value[0] == '\0')
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

static void	ft_add_env_export(t_mini *mini, char *key, char *value)
{
    t_env	*last;

    if (ft_env_exists(mini->env, key, value) == 0)
    {
        last = mini->env;
        while (last->next)
            last = last->next;
        last->next = ft_add_env_node(key, value);
    }
    if (!ft_find_key(mini->export_env, key))
    {
        last = mini->export_env;
        while (last && last->next)
            last = last->next;
        if (last)
            last->next = ft_add_env_node(key, value);
        else
            mini->export_env = ft_add_env_node(key, value);
    }
}

static int	ft_has_equal(t_mini *mini, char *str)
{
    char	**temp;
    char	*value;

    temp = ft_split(str, '=');
    if (!temp[0] || !export_validity(temp[0]))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
        ft_putstr_fd(str, STDERR_FILENO);
        ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
        free_matrix(temp);
        return (1);
	}
    else
    {
		if (temp[1])
			value = temp[1];
		else
			value = "";
        ft_add_env_export(mini, temp[0], value);
    }
    free_matrix(temp);
	return (0);
}

int	ft_export(t_mini *mini, char **str)
{
    int	i;

    if (!str[1])
        return (ft_export_env(mini, str));
    i = 0;
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
        {
            ft_putstr_fd("minishell: export: `", STDERR);
            ft_putstr_fd(str[i], STDERR);
            ft_putstr_fd("': not a valid identifier\n", STDERR);
			mini->exit_status = 1;
        }
			else
				ft_export_no_value(mini, str[i]);
		}
        i++;
    }
    return (mini->exit_status);
}
