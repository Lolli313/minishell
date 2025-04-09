/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/09 07:01:43 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*A command which exits with a zero exit status has succeeded.
A non-zero exit status indicates failure. When a command
terminates on a fatal signal whose number is N, Bash uses
the value 128+N as the exit status. If a command is not found,
the child process created to execute it returns a status of 127.
If a command is found but is not executable, the return status
is 126. In case of incorrect usagem the return status is 258.*/

int	ft_error_msg(t_mini *mini)
{
	if (!mini->path && !(ft_is_builtin(mini->line->command)))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(mini->line->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		mini->exit_status = 127;
	}
	return (mini->exit_status);
}

void	ft_mini_init(t_mini *mini)
{
	mini->stdin = dup(STDIN_FILENO);
	mini->stdout = dup(STDOUT_FILENO);
	mini->fd_in = -1;
	mini->fd_out = -1;
	mini->exit_flag = 1;
//	mini->pid = -1;
}

void	ft_execute_command(t_mini *mini)
{
	mini->path = check_external(mini->env, mini->line->command[0]);
	ft_error_msg(mini);
	if (mini->nbr_of_pipes > 0)
		ft_execute_pipeline(mini);
	else
	{
		ft_execute_heredoc(mini);
		if (ft_is_builtin(mini->line->command))
			ft_handle_builtin(mini);
		else
			ft_handle_external(mini, mini->line->command);
	}
	ft_restore_std_fds(mini);
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
		input = get_next_line(STDIN_FILENO);
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

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;

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
		{
			ft_execute_command(mini);
			//free_matrix(mini->env_array);
			mini->stdin = dup(STDIN_FILENO);
			mini->stdout = dup(STDOUT_FILENO);
			line_cleanup(mini);
		}
	}
	free_env(mini->env);
	free(mini);
	return (0);
}
