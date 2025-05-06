/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:49:29 by aakerblo          #+#    #+#             */
/*   Updated: 2025/05/06 12:19:23 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_valid_char(char c, bool first)
{
	if (first == true)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

bool	exit_validity(t_line *line)
{
	char	**temp_cmd;
	long	num;
	int		i;
	bool	char_flag;

	temp_cmd = line->command;
	char_flag = false;
	if (temp_cmd[1])
	{
		i = 0;
		while (temp_cmd[1][i])
		{
			if ((temp_cmd[1][0] == '+' || temp_cmd[1][0] == '-')
				&& char_flag == false)
				char_flag = true;
			else if (ft_isdigit(temp_cmd[1][i]) == 0)
				return (ft_printf("Error: Numeric argument required\n"), true);
			i++;
		}
		num = ft_atol(temp_cmd[1]);
		printf("%ld\n", num);
        if (num > LONG_MAX || num < LONG_MIN)
            return (ft_printf("Error: Numeric argument required\n"), true);
		if (temp_cmd[2] != NULL)
			return (ft_printf("Error: Too many arguments\n"), false);
	}
	return (true);
}

bool	echo_validity(char *str)
{
	int		i;
	bool	first;

	i = 0;
	first = true;
	if (str[1] == 0)
		return (false);
	while (str[i])
	{
		if (first == true)
		{
			if (str[i] != '-')
				return (false);
			first = false;
		}
		else if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

bool	export_validity(char *str)
{
	int	i;

	if (!str || !ft_isalpha(str[0]))
		return (false);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	token_validity(t_mini *mini)
{
	t_token	*current;

	current = mini->token;
	while (current)
	{
		if (current->next == NULL)
		{
			if (current->type == RE_INPUT || current->type == RE_OUTPUT
				|| current->type == RE_APPEND || current->type == HERE_DOC)
				return (ft_error_syntax(mini, "newline"), false);
			else if (current->type == PIPE)
				return (ft_error_syntax(mini, current->str), false);
		}
		else if ((current->type == PIPE && (current->next->type == PIPE
					|| current->index == 0)) || (current->type == RE_INPUT
				&& current->next->type != INFILE) || (current->type == RE_OUTPUT
				&& current->next->type != OUTFILE)
			|| (current->type == RE_APPEND
				&& current->next->type != APPEND_OUTFILE)
			|| (current->type == HERE_DOC && current->next->type != LIMITER))
			return (ft_handle_token_error(mini, current));
		current = current->next;
	}
	return (true);
}

/*bool	ft_handle_token_error(t_mini *mini, t_token *current)
{
    if (current->type == PIPE && current->index == 0)
        return (ft_error_syntax(mini, "|"), false);
    else if (current->next && ft_strlen(current->next->str) == 0) // Empty string after token
    {
        ft_putstr_fd("minishell: : No such file or directory\n", STDERR);
        mini->exit_status = 1;
        return (false);
    }
    else if (ft_strlen(current->str) == 0) // Empty string as a command
    {
        ft_putstr_fd("minishell: : command not found\n", STDERR);
        mini->exit_status = 127;
        return (false);
    }
    else
        return (ft_error_syntax(mini, current->next->str), false);
}
void	ft_error_syntax(t_mini *mini, char *token)
{
    ft_putstr_fd("minishell: ", STDERR);
    ft_putstr_fd("syntax error near unexpected token ", STDERR);
    if (ft_strlen(token) == 0) // Handle empty token
        ft_putstr_fd("`newline'", STDERR);
    else
    {
        ft_putstr_fd("`", STDERR);
        ft_putstr_fd(token, STDERR);
        ft_putstr_fd("'", STDERR);
    }
    ft_putstr_fd("\n", STDERR);
    mini->exit_status = 2;
}*/
