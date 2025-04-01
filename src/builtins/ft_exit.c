/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:48:03 by fmick             #+#    #+#             */
/*   Updated: 2025/04/01 09:41:37 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_strisnum(const char *str)
{
    int i = 0;

    if (!str || !*str) 
        return (0);
    if (str[i] == '-' || str[i] == '+')
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void    ft_exit(t_mini *mini, char **cmd)
{
    int exit_status;

    ft_putstr_fd("exit\n", STDERR_FILENO);
    if (cmd[1] && cmd[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
        mini->exit_status = 1;
        return; 
    }
    else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
    {
        ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
        ft_putstr_fd(cmd[1], STDERR_FILENO);
        ft_putendl_fd(": numeric argument required", STDERR_FILENO);
        mini->exit_status = 255;
    }
    else if (cmd[1])
        mini->exit_status = ft_atoi(cmd[1]);
    else
        mini->exit_status = 0;

    exit_status = mini->exit_status;
    free_env(mini->env);
    free(mini);
    exit(exit_status);
}
