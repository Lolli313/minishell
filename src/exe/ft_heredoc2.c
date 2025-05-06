/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:06:59 by aakerblo          #+#    #+#             */
/*   Updated: 2025/05/06 06:52:21 by Barmyh           ###   ########.fr       */
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
		if (g_skip != 130)
		{
			print_heredoc_warn(mini, redir, count, line);
			mini->hd_count++;
		}
		return (NULL);
	}
	else if (ft_strncmp(line, redir->str, ft_strlen(redir->str) + 1) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void	prepare_heredoc(int *count)
{
	*count = 0;
	handle_heredoc_sig();
	g_skip = 0;
}
