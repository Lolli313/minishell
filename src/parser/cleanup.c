/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:24:03 by fmick             #+#    #+#             */
/*   Updated: 2025/04/22 10:24:03 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_many(char *str1, void *str2, char *str3, char *str4)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	if (str4)
		free(str4);
}

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

void	free_mini(t_mini *mini)
{
	free_env(mini->env);
	free_env(mini->export_env);
	free(mini);
}
