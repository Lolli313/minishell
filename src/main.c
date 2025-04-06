/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/06 09:41:37 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execute_command(t_mini *mini)
{
	mini->stdin = dup(STDIN_FILENO);
	mini->stdout = dup(STDOUT_FILENO);
	mini->path = check_external(mini->env, mini->line->command[0]);

	if (mini->nbr_of_pipes > 0)
		ft_execute_pipeline(mini);
	else
	{
		if (mini->line->redirect && mini->line->redirect->type == LIMITER)
        {
            ft_pipe_heredoc(mini, mini->line); // Process the heredoc
            if (mini->line->redirect->heredoc_fd != -1)
            {
                if (dup2(mini->line->redirect->heredoc_fd, STDIN_FILENO) == -1)
                {
                    perror("dup2 heredoc_fd -> STDIN");
                    close(mini->line->redirect->heredoc_fd);
                    exit(EXIT_FAILURE);
                }
                close(mini->line->redirect->heredoc_fd); // Close after dup2
                mini->line->redirect->heredoc_fd = -1; // Mark as used
            }
        }
    	if (ft_is_builtin(mini->line->command))
		{
			ft_printf(B "Executing builtin: %s\n" RESET, mini->line->command[0]);
    	    ft_handle_builtin(mini);
		}
		else
			ft_handle_external(mini, mini->line->command);
	}
    if (dup2(mini->stdin, STDIN_FILENO) == -1)
    {
        perror("dup2 STDIN");
        exit(EXIT_FAILURE);
    }

    if (dup2(mini->stdout, STDOUT_FILENO) == -1)
    {
        perror("dup2 STDOUT");
        exit(EXIT_FAILURE);
    }
	close(mini->stdin);
    close(mini->stdout);
	free(mini->path);
	mini->path = NULL;
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
	mini->env_array = ft_env_to_array(mini->env);
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
			ft_execute_command(mini);
			close(mini->stdout);
			line_cleanup(mini);
		}
	}
	free_env(mini->env);
	free(mini);
	return (42);
}
