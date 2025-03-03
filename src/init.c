/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:41:12 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/03 17:08:01 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*add_node_token(char *str, t_token *token, int type)
{
	t_token *new_node;
	t_token	*last;

	last = ft_lstlast(&token);
	new_node = malloc(sizeof(t_token));
	new_node->str = str;
	new_node->type = type;
	if (last->index == 0)
	new_node->index = last->index + 1;
	new_node->next = NULL;
	new_node->previous = last;
	last->next = new_node;
}

void	initialize(t_token *token)
{
	token->index = 0;
	token->next = NULL;
	token->previous = NULL;
}
