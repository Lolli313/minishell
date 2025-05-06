/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/05/06 09:34:46 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mini_init(t_mini *mini)
{
	mini->stdin = dup(STDIN);
	mini->stdout = dup(STDOUT);
	mini->fd_in = -1;
	mini->fd_out = -1;
	mini->pipe_in = -1;
	mini->pipe_out = -1;
	mini->fd = -1;
	mini->exit_status = 0;
	mini->exit_flag = 1;
	mini->skibidi = 0;
	mini->hd_count = 0;
	mini->line = NULL;
}

int	ft_parse_input(t_mini *mini)
{
	char	*input;

	mini->interactive = isatty(STDIN);
	if (mini->interactive)
		input = readline(PROMPT);
	else
		input = get_next_line(STDIN);
	if (!input)
	{
		if (mini->interactive)
			ft_printf("exit\n");
		return (0);
	}
	if (*input)
		add_history(input);
	if (g_skip == 130)
		mini->exit_status = 130;
	g_skip = 1;
	parse_string(mini, input);
	free(input);
	return (1);
}

static void	the_end(t_mini *mini)
{
	rl_clear_history();
	ft_close(mini->stdin);
	ft_close(mini->stdout);
	free_mini(mini);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;
	int		exit;

	(void)ac;
	(void)av;
	mini = malloc(sizeof(t_mini));
	ft_mini_init(mini);
	mini->env = ft_init_env(envp);
	mini->export_env = ft_init_export_env_(envp);
	while (mini->exit_flag)
	{
		handle_signals();
		if (!ft_parse_input(mini))
			break ;
		if (mini->line)
			ft_execute_command(mini);
		g_skip = 0;
		line_cleanup(mini);
	}
	exit = mini->exit_status;
	the_end(mini);
	return (exit);
}
