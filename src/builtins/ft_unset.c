/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:22 by fmick             #+#    #+#             */
/*   Updated: 2025/05/12 13:03:47 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_key(t_env **env, char *key)
{
	t_env	*lst;
	t_env	*prev;

	lst = *env;
	prev = NULL;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			if (prev == NULL)
				*env = lst->next;
			else
				prev->next = lst->next;
			free(lst->key);
			free(lst->value);
			free(lst);
			return ;
		}
		prev = lst;
		lst = lst->next;
	}
}

int	ft_unset(t_mini *mini, char **av)
{
	int	i;
	int	error;

	error = 0;
	i = 1;
	if (!av[i])
		return (0);
	while (av[i])
	{
		ft_unset_key(&(mini->env), av[i]);
		ft_unset_key(&(mini->export_env), av[i]);
		i++;
	}
	mini->exit_status = error;
	return (0);
}
