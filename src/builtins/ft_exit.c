/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:48:03 by fmick             #+#    #+#             */
/*   Updated: 2025/05/06 11:17:20 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strisnum(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_exit_util(t_mini *mini, char **cmd)
{
    long	exit;

    if (ft_strisnum(cmd[1]) == 0)
    {
        ft_putstr_fd("minishell: exit: ", STDERR);
        ft_putstr_fd(cmd[1], STDERR);
        ft_putstr_fd(": numeric argument required\n", STDERR);
        mini->exit_status = 2;
        mini->exit_flag = 0;
    }
    else
    {
        exit = ft_atol(cmd[1]); // Use ft_atol to handle large numbers
        if ((exit == LONG_MAX && ft_strcmp(cmd[1], "9223372036854775807") != 0)
            || (exit == LONG_MIN && ft_strcmp(cmd[1], "-9223372036854775808") != 0))
        {
            ft_putstr_fd("minishell: exit: ", STDERR);
            ft_putstr_fd(cmd[1], STDERR);
            ft_putstr_fd(": numeric argument required\n", STDERR);
            mini->exit_status = 2;
            mini->exit_flag = 0;
        }
        else
        {
            mini->exit_status = (unsigned char)(exit % 256);
            mini->exit_flag = 0;
        }
    }
}

void	ft_exit(t_mini *mini, char **cmd)
{
	printf("exit\n");
	if (cmd[1] && cmd[2])
	{
		if (ft_strisnum(cmd[1]) == 0)
		{
			mini->exit_status = 2;
			mini->exit_flag = 0;
		}
		else
			mini->exit_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
	}
	else if (cmd[1])
	{
		ft_exit_util(mini, cmd);
	}
	else
		mini->exit_flag = 0;
}
