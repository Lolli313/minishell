/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:57 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/07 17:32:24 by aakerblo         ###   ########.fr       */
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
	{
		current = current->next;
	}
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
//	TODO here make a function that deals with token relativity (ex. if the current type is COMMAND and the previous type is also COMMAND,
//	make the current one into type ARGUMENT and then replace the current type with the new type)	
	return (token);
}

void	arguments_before_pipe(t_token *token)
{
	t_token	*current;

	current = token->next;
	while (current)
	{
		//if (current->previous->type == PIPE && current->type == COMMAND)
		//	current = current->next;
		if (current->type == COMMAND)
		{
			if (current->previous->type != PIPE)
				current->type = ARGUMENT;
			current = current->next;
		}
		else
			current = current->next;
	}
}

void	check_infile(t_token *token)
{
	(void)token;
	
}

void	check_outfile(t_token *token)
{
	(void)token;
}

void	check_file(t_token *token)
{
	if (token->type == RE_INPUT)
		check_infile(token);
	else
		check_outfile(token);
}

void	token_relativity(t_token *token)
{
	arguments_before_pipe(token);
	check_file(token);
}

t_token	*tokenizer(char *str, t_type type, t_token *token)
{
	token = add_node_token(token, str, type);
	token_relativity(token);
	return (token);
}
