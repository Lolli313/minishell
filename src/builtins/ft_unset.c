/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:22 by fmick             #+#    #+#             */
/*   Updated: 2025/03/07 08:39:35 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_node(t_mini *mini, t_env *env)
{
	if (env->key != NULL)
		free (env->key);
	if (env->value != NULL)
		free (env->value);
	free (env);
}

// env variables
// handles "_" notcate the variable specified and then deletes it
// from the linked list of  being able to unset
int		ft_unset(t_mini *mini, char **array)
{
	t_env	*env;
	t_env	*tmp;

	env = mini->env;
	if (array[1] == NULL)
		return 0;
	while (env && env->next)
	{
		if (ft_strcmp(array[1], env->next->key) == 0)
		{
			tmp = env->next->next;
			ft_free_node(mini, env->next);
			env->next = tmp;
			return 0;
		}
		env = env->next;
	}
	return 0;
}
