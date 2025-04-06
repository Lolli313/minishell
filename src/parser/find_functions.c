/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:50:08 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/29 11:47:38 by Barmyh           ###   ########.fr       */
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
			ft_printf(G "find_functions: Found pipe at token: %s\n"RESET, token->str);
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
		if (current->type == COMMAND)
			return (current);
		current = current->next;
	}
	return (NULL);
}
