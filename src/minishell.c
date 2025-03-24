/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:39:10 by fmick             #+#    #+#             */
/*   Updated: 2025/03/24 10:18:56 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_split(char **arr)
{
	int	i = 0;

	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}


static void	ft_free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}


int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**cmd_args;
	t_mini	*mini;

	signal(SIGINT, &ft_handle_sigint);
	(void)ac;
	(void)av;
	
	mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
		return (1);
	mini->exit_flag = 1;
	mini->env = ft_init_env(envp);
	while (mini->exit_flag == 1)
	{
		input = readline(G "😭 minishell$ " RESET);
		if (!input) // If readline fails (e.g., CTRL+D)
		{
			printf("exit\n");
			break;
		}
		if (*input)
		{
			add_history(input);
			printf("Received input: %s\n", input);
		}
		cmd_args = ft_split(input, ' ');
		if (cmd_args && cmd_args[0])
		{
			if (strcmp(input, "exit") == 0)
			{
				mini->exit_flag = 0;
				ft_free_split(cmd_args);
				free(input);
				break;
			}
			ft_handle_builtin(cmd_args, mini);
	//		ft_handle_pipes(mini, envp);
		}
		ft_free_split(cmd_args);
		free(input);
	}
	ft_free_env(mini->env);
	free(mini);
	return (0);
}
