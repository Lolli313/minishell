/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:39:17 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/28 17:40:30 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_operator_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

t_type	get_operator_type(char *op, int len)
{
	if (len == 1)
	{
		if (op[0] == '<')
			return (RE_INPUT);
		else if (op[0] == '>')
			return (RE_OUTPUT);
		else if (op[0] == '|')
			return (PIPE);
	}
	else if (len == 2)
	{
		if (op[0] == '<' && op[1] == '<')
			return (HERE_DOC);
		else if (op[0] == '>' && op[1] == '>')
			return (RE_APPEND);
	}
	return (COMMAND);
}

t_token	*if_operator(t_token *token, char *input, int *i)
{
	char	op[2];
	int		op_len;

	op_len = 1;
	op[0] = input[(*i)++];
	op[1] = 0;
	if (input[*i] == op[0] && (op[0] == '<' || op[0] == '>'))
	{
		op[1] = input[(*i)++];
		op_len = 2;
	}
	token = add_node_token(token, ft_strdup(op), get_operator_type(op, op_len));
	return (token);
}
