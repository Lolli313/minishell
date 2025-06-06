/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:50:08 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/16 10:35:29 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*find_pipe(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == PIPE)
		{
			return (current->next);
		}
		current = current->next;
	}
	return (NULL);
}

t_token	*find_command(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == COMMAND || current->type == ARGUMENT)
			return (current);
		current = current->next;
	}
	return (NULL);
}
