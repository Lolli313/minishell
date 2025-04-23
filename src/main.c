/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/23 15:15:43 by fmick            ###   ########.fr       */
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
}

int	ft_parse_input(t_mini *mini)
{
	char	*input;

	mini->interactive = 1;
	//mini->interactive = isatty(STDIN);
	if (mini->interactive)
	{
		input = readline(G "😭 minishell$ " RESET);
	}
	else
	{
		input = get_next_line(STDIN);
	}
	if (!input)
	{
		if (mini->interactive)
			ft_printf("exit\n");
		return (0);
	}
	parse_string(mini, input);
	if (*input)
		add_history(input);
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
		g_skip = true;
		if (mini->line)
			ft_execute_command(mini);
		g_skip = false;
		line_cleanup(mini);
	}
	exit = mini->exit_status;
	the_end(mini);
	return (exit);
}
