/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:39:10 by fmick             #+#    #+#             */
/*   Updated: 2025/03/06 13:39:09 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static t_env	*ft_add_node(char *key, char *value)
{
	t_env *env = malloc(sizeof(t_env));
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = NULL;
	return env;
}*/

static void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array); // Free the array itself
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	int		exit;
	t_env	*env;

	exit = 1;
	signal(SIGINT, &ft_handle_sigint);
	(void)ac;
	(void)av;
	
	env = ft_init_env(envp);
	ft_env(env);
	while (exit == 1)
	{
		input = readline(G "😭 minishell$ " RESET);
		if (*input)
			add_history(input);

		if (strcmp(input, "exit") == 0)
		{
			exit = 0;
			free(input);
			break;
		}
		else if (strncmp(input, "cd", 2) == 0)
		{
			char **args = ft_split(input, ' ');
			ft_cd(args, env);
			ft_free_array(args);
		}
		else if (strncmp(input, "env", 3) == 0)
		{
			ft_env(env);
		}
		else if (strncmp(input, "pwd", 3) == 0)
		{
			ft_pwd();
		}
		else if (strncmp(input, "echo", 4) == 0)
		{
			char **argvs = ft_split(input, ' ');
			ft_echo(argvs);
			ft_free_array(argvs);
		}
	}
	return (0);
}
