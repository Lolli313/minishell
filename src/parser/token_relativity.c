/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_relativity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:45:45 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/17 10:17:17 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	arguments_before_pipe(t_token *token)
{
	t_token	*current;
	bool	flag_command;

	if (!token)
		return ;
	current = token;
	flag_command = false;
	while (current)
	{
		if (current->type == COMMAND)
		{
			if (flag_command == true)
				current->type = ARGUMENT;
			else
				flag_command = true;
		}
		else if (current->type == PIPE)
			flag_command = false;
		current = current->next;
	}
}

void	find_redirect(t_token *token)
{
	t_token	*current;

	current = token->next;
	while (current)
	{
		if (current->previous->type == RE_OUTPUT && current->type == COMMAND)
			current->type = OUTFILE;
		else if (current->previous->type == RE_APPEND
			&& current->type == COMMAND)
			current->type = APPEND_OUTFILE;
		else if (current->previous->type == RE_INPUT
			&& current->type == COMMAND)
			current->type = INFILE;
		else if (current->previous->type == HERE_DOC
			&& current->type == COMMAND)
			current->type = LIMITER;
		current = current->next;
	}
}

void	token_relativity(t_token *token)
{
	find_redirect(token);
	arguments_before_pipe(token);
}
