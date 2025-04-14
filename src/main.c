/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/14 12:01:45 by fmick            ###   ########.fr       */
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

#include "minishell.h"

/*
static int	ft_permission_error(t_mini *mini, char *path, char **command)
{
	if (access(path, F_OK) == -1)
	{
		ft_print_error(mini, command[0], "No such file or directory", 127);
		return (1);
	}
	if (access(path, X_OK) == -1)
	{
		ft_print_error(mini, command[0], "Permission denied", 126);
		return (1);
	}
}*/
static void	ft_print_error(t_mini *mini, char *line, char *message,
		int exit_status)
{
	ft_putstr_fd("minishell: ", STDERR);
	if (line)
	{
		ft_putstr_fd(line, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putendl_fd(message, STDERR);
	mini->exit_status = exit_status;
	mini->skibidi = 1;
}

void	ft_error_msg(t_mini *mini)
{
	DIR	*dir;

	dir = opendir(mini->line->command[0]);
	if (dir != NULL)
		ft_print_error(mini, mini->line->command[0], "Is a directory", 126);
	else if (!ft_strchr(mini->line->command[0], '/'))
		ft_print_error(mini, mini->line->command[0], "command not found", 127);
	else if (access(mini->line->command[0], F_OK) != 0)
		ft_print_error(mini, mini->line->command[0],
			"No such file or directory", 127);
	else if (access(mini->line->command[0], X_OK) != 0)
		ft_print_error(mini, mini->line->command[0], "Permission denied", 126);
	if (dir)
		closedir(dir);
}

void	ft_mini_init(t_mini *mini)
{
	mini->stdin = dup(STDIN);
	mini->stdout = dup(STDOUT);
	mini->fd_in = -1;
	mini->fd_out = -1;
	mini->pipe_in = -1;
	mini->pipe_out = -1;
	mini->exit_status = 0;
	mini->exit_flag = 1;
	mini->skibidi = 0;
}

void	ft_single_command(t_mini *mini)
{
//	ft_error_msg(mini);
	ft_execute_heredoc(mini);
	ft_handle_redirections(mini);
	if (ft_is_builtin(mini->line->command))
		ft_handle_builtin(mini);
	else
		ft_handle_external(mini, mini->line->command);
}

void	ft_execute_command(t_mini *mini)
{
	if (mini->nbr_of_pipes == 0)
		ft_single_command(mini);
	else
		ft_execute_pipeline(mini);
	ft_close(mini->fd_in);
	ft_close(mini->fd_out);
	ft_close(mini->pipe_in);
	ft_close(mini->pipe_out);
	mini->pipe_in = -1;
	mini->pipe_out = -1;
	ft_restore_std_fds(mini);
}

int	ft_parse_input(t_mini *mini)
{
	char	*input;

	mini->interactive = 1;
	// mini->interactive = isatty(STDIN);
	if (mini->interactive)
		input = readline(G "😭 minishell$ " RESET);
	else
		input = get_next_line(STDIN);
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
		line_cleanup(mini);
	}
	exit = mini->exit_status;
	ft_close(mini->stdin);
	ft_close(mini->stdout);
	free_env(mini->env);
	free_env(mini->export_env);
	free(mini);
	return (exit);
}
