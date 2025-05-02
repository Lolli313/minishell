/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:06:59 by aakerblo          #+#    #+#             */
/*   Updated: 2025/05/02 11:06:59 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_heredoc_warn(t_mini *mini, t_re *redir, int count, char *line)
{
	printf("minishell: warning: here-document at line");
	printf(" %d", mini->hd_count + count + 1);
	printf(" delimited by end-of-file");
	printf(" (wanted `%s')\n", redir->str);
	free(line);
}

char	*handle_heredoc_line(t_mini *mini, t_re *redir, int count)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		print_heredoc_warn(mini, redir, count, line);
		return (NULL);
	}
	else if (ft_strncmp(line, redir->str, ft_strlen(redir->str) + 1) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void	prepare_heredoc(int *count, int *i, int *pipefd)
{
	*count = 0;
	handle_heredoc_sig();
	*i = 0;
	g_skip = 1;
	ft_close(pipefd[0]);
}
