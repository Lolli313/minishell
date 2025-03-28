/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structurize_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:45:08 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/28 18:46:55 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_re	*add_node_redirect(t_token *token)
{
	t_re	*new_node;

	new_node = malloc(sizeof(t_re));
	if (!new_node)
		return (0);
	new_node->str = ft_strdup(token->str);
	new_node->type = token->type;
	new_node->next = NULL;
	return (new_node);
}

t_re	*structurize_redirect(t_token *token)
{
	t_token	*current;
	t_re	*redirect;
	t_re	*first;

	first = NULL;
	current = token;
	while (current && current->type != PIPE)
	{
		if (first == NULL && (current->type == INFILE
				|| current->type == OUTFILE || current->type == APPEND_OUTFILE
				|| current->type == LIMITER))
		{
			first = add_node_redirect(current);
			redirect = first;
		}
		else if (current->type == INFILE || current->type == OUTFILE
			|| current->type == APPEND_OUTFILE || current->type == LIMITER)
		{
			redirect->next = add_node_redirect(current);
			redirect = redirect->next;
		}
		current = current->next;
	}
	return (first);
}

char	**make_command_into_array(t_token *token)
{
	t_token	*current;
	char	**array;
	size_t	counter;
	size_t	i;

	counter = calculate_number_of_commands(token);
	if (counter == 0)
		return (NULL);
	current = find_command(token);
	array = ft_calloc(counter + 1, sizeof(char *));
	if (current->str)
		array[0] = ft_strdup(current->str);
	current = current->next;
	i = 1;
	while (current && current->type != PIPE)
	{
		if (current->type == ARGUMENT)
			array[i++] = ft_strdup(current->str);
		current = current->next;
	}
	return (array);
}

t_line	*add_node_line(t_token *token)
{
	t_line	*new_node;

	new_node = malloc(sizeof(t_line));
	if (!new_node)
		return (NULL);
	new_node->command = make_command_into_array(token);
	new_node->redirect = structurize_redirect(token);
	new_node->next = NULL;
	return (new_node);
}
