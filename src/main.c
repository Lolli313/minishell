/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/01 11:11:42 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// unsure how to deal with 'ABC=hola' as input
// do we add that to the env variables or no

// TODO signals (CTRL + D and CTRL + \),
// look into echo -n and how the syntax should be handled

void	ft_execute_command(t_mini *mini, char **envp)
{
	if (mini->line->redirect)
	{
		mini->hd_count = ft_count_heredocs(mini->line->redirect);
		if (mini->hd_count > 0)
		{
			ft_allocate_heredoc_pipes(mini);
			ft_prepare_heredocs(mini);
		}
	}
	if (mini->nbr_of_pipes > 0)
	{
		ft_printf(R "Handling pipeline with %d pipes...\n" RESET,
			mini->nbr_of_pipes);
		ft_handle_pipes(mini, envp);
	}
	else
	{
		// Single command execution
		if (mini->line->command && mini->line->command[0])
		{
			ft_handle_redirections(mini);
			if (ft_is_builtin(mini->line->command))
			{
				ft_handle_builtin(mini);
			}
			else
			{
				if (mini->line->command && mini->line->command[0])
				{
					ft_handle_redirections(mini);
					if (ft_is_builtin(mini->line->command))
					{
						ft_handle_builtin(mini);
					}
					else
					{
						ft_handle_external(mini, mini->line->command, envp);
					}
				}
			}
		}
	}
	ft_cleanup_heredocs(mini);
}

int	ft_parse_input(t_mini *mini)
{
	char	*input;

	mini->interactive = isatty(STDIN_FILENO);
	if (mini->interactive)
		input = readline(G "😭 minishell$ " RESET);
	else
		input = get_next_line(STDIN_FILENO); // Read input non-interactively
	if (!input)
	{
		if (mini->interactive)
			ft_printf("exit\n");
		return (0); // Signal to exit the shell
	}
	ft_printf(B "Received input: %s\n" RESET, input);
	parse_string(mini, input);
	if (*input)
		add_history(input);
	free(input);
	return (1); // Signal to continue the shell
}

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;

	handle_signals();
	(void)ac;
	(void)av;
	mini = malloc(sizeof(t_mini));
	mini->exit_flag = 1;
	mini->env = ft_init_env(envp);
	while (mini->exit_flag)
	{
		if (!ft_parse_input(mini))
			break ;
		if (mini->line)
		{
			mini->stdout = dup(STDOUT_FILENO); // Save the original STDOUT
			if (mini->stdout == -1)
			{
				perror("dup");
				line_cleanup(mini);
				continue ;
			}
			ft_execute_command(mini, envp);
			if (dup2(mini->stdout, STDOUT_FILENO) == -1)
				perror("dup2 restore");
			close(mini->stdout);
			line_cleanup(mini);
		}
	}
	free_env(mini->env);
	free(mini);
	return (42);
}
