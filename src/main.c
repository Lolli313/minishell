/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:39:10 by fmick             #+#    #+#             */
/*   Updated: 2025/03/07 12:48:26 by fmick            ###   ########.fr       */
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
}

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
} */

int	main(int ac, char **av, char **envp)
{
	char	*input;
	int		exit;
	t_mini	*mini;

	exit = 1;
	signal(SIGINT, &ft_handle_sigint);
	(void)ac;
	(void)av;
	
	mini = (t_mini *)malloc(sizeof(t_mini));
	mini->exit_flag = 1;
	mini->env = ft_init_env(envp);
	while (mini->exit_flag == 1)
	{
		input = readline(G "😭 minishell$ " RESET);
		if (*input)
		{
			add_history(input);
			printf("Received input: %s\n", input);
			
			// testing builtins
			// ft_env(mini->env);
			ft_pwd();
			// ft_export(mini->env, mini->env->key, mini->env->value);
			// ft_echo(av);
		}

		if (strcmp(input, "exit") == 0)
		{
			mini->exit_flag = 0;
			free(input);
			break;
		}
	}
	return (0);
}
