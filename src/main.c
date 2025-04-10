/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/10 18:31:25 by Barmyh           ###   ########.fr       */
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


void	ft_error_msg(t_mini *mini)
{
	DIR	*dir;

	dir = opendir(mini->line->command[0]);
	ft_putstr_fd("minishell: ", STDERR);
    ft_putstr_fd(mini->line->command[0], STDERR);
	if (ft_strchr(mini->line->command[0], '/') == NULL)
	{
		ft_putstr_fd(": command not found\n", STDERR);
		mini->exit_status = 127;
	}
    else if (access(mini->line->command[0], F_OK) != 0)
    {
        ft_putendl_fd(": No such file or directory", STDERR_FILENO);
        mini->exit_status = 127;
    }
    else if (dir != NULL)
    {
        ft_putendl_fd(": Is a directory", STDERR_FILENO);
        mini->exit_status = 126;
    }
    else if (access(mini->line->command[0], X_OK) != 0)
    {
        ft_putendl_fd(": Permission denied", STDERR_FILENO);
        mini->exit_status = 126;
    }
    else
    {
        ft_putendl_fd(": Unknown error", STDERR_FILENO);
        mini->exit_status = 1;
    }
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
//	mini->pid = -1;
}

void	ft_execute_command(t_mini *mini)
{
//	close_all(mini);
	mini->path = check_external(mini->env, mini->line->command[0]);
	if (!ft_is_builtin(mini->line->command) && !mini->path)
		ft_error_msg(mini);
	if (mini->nbr_of_pipes > 0)
	{
	//	printf("Executing pipeline with %d pipes\n", mini->nbr_of_pipes);
		ft_execute_pipeline(mini);
	}
	else
	{
	//	printf("Executing command: %s\n", mini->line->command[0]);
		ft_execute_heredoc(mini);
		ft_handle_redirections(mini);
		if (ft_is_builtin(mini->line->command))
			ft_handle_builtin(mini);
		else
			ft_handle_external(mini, mini->line->command);
	}
	ft_close(mini->pipe_in);
	ft_close(mini->pipe_out);
	mini->pipe_in = -1;
	mini->pipe_out = -1;
	ft_restore_std_fds(mini);
	free(mini->path);
	mini->path = NULL;
}

int	ft_parse_input(t_mini *mini)
{
	char	*input;

	mini->interactive = 1;
	//mini->interactive = isatty(STDIN);
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

	(void)ac;
	(void)av;
	int 	exit;
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
