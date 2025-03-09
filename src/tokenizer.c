/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:57 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/09 19:13:00 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*find_last(t_token *token)
{
	t_token	*current;

	if (token == 0)
		return (0);
	current = token;
	while (current->next)
		current = current->next;
	return (current);
}

t_token	*add_node_token(t_token *token, char *str, t_type type)
{
	t_token *new_node;
	t_token	*last;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
	return (0);
	new_node->str = str;
	new_node->type = type;
	new_node->next = NULL;
	if (token == NULL)
	{
		new_node->index = 0;
		new_node->previous = NULL;
		return (new_node);
	}
	last = find_last(token);
	new_node->index = last->index + 1;
	new_node->previous = last;
	last->next = new_node;
	return (token);
}

void	arguments_before_pipe(t_token *token)
{
	t_token	*current;
	bool	flag_command;

	if (!token)
		return ;
	current = token;
	flag_command = false;
	/*while (current->type != COMMAND)
	{
		current = current->next;
		if (!current)
			return ;
	}
	current = current->next;
	while (current)
	{
		if (current->type == COMMAND)
		{
			if (current->previous->type != PIPE)
				current->type = ARGUMENT;
			current = current->next;
		}
		else
			current = current->next;
	}*/
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
		if (current->previous->type == RE_INPUT || current->previous->type == APPEND)
			current->type = INFILE;
		else if (current->previous->type == RE_OUTPUT)
			current->type = OUTFILE;
		else if (current->previous->type == HERE_DOC)
			current->type = LIMITER;
		current = current->next;
	}
}

void	token_relativity(t_token *token)
{
	find_redirect(token);
	arguments_before_pipe(token);
}

t_token	*tokenizer(char *str, t_type type, t_token *token)
{
	token = add_node_token(token, str, type);
//	token_relativity(token);
	return (token);
}
