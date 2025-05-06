/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:31:21 by fmick             #+#    #+#             */
/*   Updated: 2025/05/06 10:18:56 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_mini *mini, char **cmd, int i, int error)
{
	if (error == 1)
	{
		ft_putstr_fd("minishell: export: `", STDERR);
		ft_putstr_fd(cmd[i], STDERR);
		ft_putstr_fd("': not a valid identifier\n", STDERR);
		mini->skibidi = 0;
		mini->exit_status = 1;
	}
}

int	ft_cd_error(char *path, int error)
{
	ft_putstr_fd("minishell: cd: ", STDERR);
	if (path)
	{
		ft_putstr_fd(path, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (error == 0)
		ft_putstr_fd("HOME not set\n", STDERR);
	else if (error == 1)
		ft_putstr_fd("can't change directory\n", STDERR);
	else if (error == 2)
		ft_putstr_fd("too many arguments\n", STDERR);
	else if (error == 3)
		ft_putstr_fd("No such file or directory\n", STDERR);
	return (1);
}

void	ft_error_syntax(t_mini *mini, char *token)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd("syntax error near unexpected token ", STDERR);
	ft_putstr_fd("`", STDERR);
	ft_putstr_fd(token, STDERR);
	ft_putstr_fd("'\n", STDERR);
	mini->exit_status = 2;
}

void	ft_print_error(t_mini *mini, char *line, char *msg, int exit)
{
	ft_putstr_fd("minishell: ", STDERR);
	if (line)
	{
		ft_putstr_fd(line, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putendl_fd(msg, STDERR);
	mini->exit_status = exit;
}

void	ft_error_msg(t_mini *mini, char *cmd)
{
	DIR		*dir;

	if (g_skip == 2 && ft_strlen(cmd) == 0)
	{
		g_skip = 1;
		mini->exit_status = 0;
		return ;
	}
	dir = opendir(cmd);
	if (!ft_strchr(cmd, '/'))
		ft_print_error(mini, cmd, "command not found", 127);
	else if (dir != NULL)
	{
		closedir(dir);
		ft_print_error(mini, cmd, "Is a directory", 126);
		mini->exit_flag = 0;
	}
	else if (access(cmd, F_OK) != 0)
		ft_print_error(mini, cmd, "No such file or directory", 127);
	else if (access(cmd, X_OK) != 0)
		ft_print_error(mini, cmd, "Permission denied", 126);
}
