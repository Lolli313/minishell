/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:42:09 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/16 10:22:04 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*find_last_token(t_token *token)
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
	t_token	*new_node;
	t_token	*last;

	if (!str)
		return (token);
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
	last = find_last_token(token);
	new_node->index = last->index + 1;
	new_node->previous = last;
	last->next = new_node;
	return (token);
}

static void	remove_empty_tokens(t_mini *mini)
{
	t_token *curr = mini->token;
	t_token *prev = NULL;
	t_token *next;

	while (curr)
	{
		next = curr->next;
		if (!curr->str || !*curr->str)
		{
			if (prev)
				prev->next = next;
			else
				mini->token = next;

			if (next)
				next->previous = prev;
			free(curr->str);
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
	curr = mini->token;
    int idx = 0;
    while (curr)
    {
        curr->index = idx++;
        curr = curr->next;
    }
}

t_token	*tokenize_input(t_mini *mini, char *input)
{
	int		i;
	char	*word;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (is_operator_char(input[i]))
			mini->token = if_operator(mini->token, input, &i);
		else
		{
			word = extract_word(&mini->extract, input, &i);
			if (word == NULL)
				return (line_cleanup(mini), NULL);
			mini->token = add_node_token(mini->token, word, COMMAND);
		}
	}
	if (mini->token == NULL)
		return (line_cleanup(mini), NULL);
	token_relativity(mini->token);
	expand_variables(mini);
	remove_empty_tokens(mini);
	if (token_validity(mini) == false)
		return (line_cleanup(mini), NULL);
	return (mini->token);
}
