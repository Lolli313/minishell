/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:48:03 by fmick             #+#    #+#             */
/*   Updated: 2025/04/01 12:47:49 by fmick            ###   ########.fr       */
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
	bool eflag;

	eflag = true;
	ft_printf("exit\n");
    if (cmd[1] && ft_strisnum(cmd[1]) && exit_validity(mini->line) == false)
    {
        mini->exit_status = 255;
		eflag = false;
    }
    else if (cmd[1])
        mini->exit_status = ft_atoi(cmd[1]);
    else
	{
        mini->exit_status = 0;
	}
	if (eflag == true)
	{
    	exit_status = mini->exit_status;
		line_cleanup(mini);
    	free_env(mini->env);
    	free(mini);
    	exit(exit_status);
	}
}
