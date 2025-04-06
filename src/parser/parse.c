/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:31 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/06 09:57:48 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_variables(t_mini *mini)
{
	t_token	*current;
	int		i;

	current = mini->token;
	while (current)
	{
		i = 0;
		while (current->str[i])
		{
			if (current->str[i] == '\'')
				current->str = handle_single_quote(current->str, current->str
						+ i, &i);
			else if (current->str[i] == '\"')
				current->str = handle_double_quote(mini, current->str,
						current->str + i, &i);
			else if (current->str[i] == '$')
				current->str = handle_dollar_sign(mini, current->str,
						current->str + i, &i);
			else
				i++;
		}
		current = current->next;
	}
}

t_line	*structurize_line(t_mini *mini)
{
	t_line	*current;
	t_token	*next_pipe;
	size_t	pipes;
	size_t	i;

	pipes = count_pipes(mini->token);
	mini->nbr_of_pipes = pipes;
	i = 0;
	mini->line = add_node_line(mini->token);
	current = mini->line;
	next_pipe = mini->token;
	while (i < pipes)
	{
		next_pipe = find_pipe(next_pipe);
		current->next = add_node_line(next_pipe);
		current = current->next;
		i++;
	}
	return (mini->line);
}

void	parse_string(t_mini *mini, char *line)
{
	if (ft_strncmp(line, "\0", 1) == 0)
		return ;
	mini->token = NULL;
	mini->line = NULL;
	mini->token = tokenize_input(mini, line);
	if (mini->token == NULL)
		return ;
	//print_tokens(mini->token);
	mini->line = structurize_line(mini);
	if (mini->line == NULL)
		return ;
	//print_lines(mini->line);
}
