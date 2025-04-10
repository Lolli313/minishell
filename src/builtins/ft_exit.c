/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:48:03 by fmick             #+#    #+#             */
/*   Updated: 2025/04/10 16:29:51 by Barmyh           ###   ########.fr       */
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

void	ft_exit(t_mini *mini, char **cmd)
{
	int	exit_code;

   // ft_putstr_fd("exit\n", STDERR); uncomment when done
	if (cmd[1] && cmd[2])
	{
		mini->exit_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		return ;
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		mini->exit_status = 2;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
		return ;
	}
	else if (cmd[1])
	{
        exit_code = ft_atoi(cmd[1]);
        mini->exit_status = (unsigned char)(exit_code % 256);
        mini->exit_flag = 0;
	}
	else
	{
		mini->exit_status = 0;
		mini->exit_flag = 0;
	}
}