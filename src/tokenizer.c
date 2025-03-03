/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:20:57 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/03 17:07:59 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	tokenizer(char *str, int type, t_token *token)
{
	t_token	*last;

	token = add_node_token(str, token, type);
	if (!token->index)
		
}
