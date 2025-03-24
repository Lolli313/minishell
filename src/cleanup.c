/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 11:55:53 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/22 11:55:53 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_redirect(t_re *redirect)
{
	t_re	*current;
	t_re	*next;

	current = redirect;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

void	line_cleanup(t_mini *mini)
{
	t_token	*token;
	t_token	*temp_token;
	t_line	*line;
	t_line	*temp_line;

	token = mini->token;
	while (token)
	{
		temp_token = token;
		token = token->next;
		free(temp_token->str);
		free(temp_token);
	}
	mini->token = NULL;
	line = mini->line;
	while (line)
	{
		temp_line = line;
		line = line->next;
		free_matrix(temp_line->command);
		free_redirect(temp_line->redirect);
		free(temp_line);
	}
	mini->line = NULL;
}
	