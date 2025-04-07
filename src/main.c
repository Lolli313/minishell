/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:56 by aakerblo          #+#    #+#             */
/*   Updated: 2025/04/07 08:02:32 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execute_command(t_mini *mini)
{
	mini->stdin = dup(STDIN_FILENO);
	mini->stdout = dup(STDOUT_FILENO);
	mini->path = check_external(mini->env, mini->line->command[0]);

	if (mini->nbr_of_pipes > 0)
		ft_execute_pipeline(mini);
	else
	{
		ft_execute_heredoc(mini);
    	if (ft_is_builtin(mini->line->command))
    	    ft_handle_builtin(mini);
		else
			ft_handle_external(mini, mini->line->command);
	}
	dup2(mini->stdin, STDIN_FILENO);
	dup2(mini->stdout, STDOUT_FILENO);
	ft_restore_std_fds(mini);
	free(mini->path);
	mini->path = NULL;
}

int	ft_parse_input(t_mini *mini)
{
	char	*input;

	mini->interactive = isatty(STDIN_FILENO);
	if (mini->interactive)
		input = readline(G "😭 minishell$ " RESET);
	else
		input = get_next_line(STDIN_FILENO); //non-interactive
	if (!input)
	{
		if (mini->interactive)
			ft_printf("exit\n");
		return (0); //exit 
	}
	parse_string(mini, input);
	if (*input)
		add_history(input);
	free(input);
	return (1); //continue
}

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;

	handle_signals();
	(void)ac;
	(void)av;
	mini = malloc(sizeof(t_mini));
	mini->exit_flag = 1;
	mini->env = ft_init_env(envp);
	mini->env_array = ft_env_to_array(mini->env);
	while (mini->exit_flag)
	{
		if (!ft_parse_input(mini))
			break ;
		if (mini->line)
		{
			ft_execute_command(mini);
			close(mini->stdout);
			line_cleanup(mini);
		}
	}
	free_env(mini->env);
	free(mini);
	return (42);
}
