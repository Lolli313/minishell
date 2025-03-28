/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:54:14 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/28 18:55:41 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	calculate_number_of_commands(t_token *token)
{
	t_token	*current;
	size_t	counter;

	current = token;
	counter = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == COMMAND || current->type == ARGUMENT)
			counter++;
		current = current->next;
	}
	return (counter);
}

size_t	count_pipes(t_token *token)
{
	t_token	*current;
	size_t	counter;

	current = token;
	counter = 0;
	while (current)
	{
		if (current->type == PIPE)
			counter++;
		current = current->next;
	}
	return (counter);
}
