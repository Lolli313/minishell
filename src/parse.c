/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:31 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/12 12:33:50 by aakerblo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_builtin(char *command)
{
	if (!ft_strncmp(command, "echo", 5))
		return (true);
	else if (!ft_strncmp(command, "cd", 3))
		return (true);
	else if (!ft_strncmp(command, "pwd", 4))
		return (true);
	else if (!ft_strncmp(command, "export", 7))
		return (true);
	else if (!ft_strncmp(command, "unset", 6))
		return (true);
	else if (!ft_strncmp(command, "env", 4))
		return (true);
	else if (!ft_strncmp(command, "exit", 5))
		return (true);
	else if (!ft_strncmp(command, "$?", 3))
		return (true);
	else
		return (false);
}

bool	check_external(char *command)
{
	char	**all_paths;
	char	*temp;
	char	*str;
	char	*str1;

	temp = getenv("PATH");
	all_paths = ft_split(temp + 5, ':');
	while (*all_paths)
	{
		str = ft_strjoin(*all_paths, "/");
		str1 = ft_strjoin(str, command);
		free(str);
		if (access(str1, X_OK) == 0)
			return (free(str1), true);
		free(str1);
		all_paths++;
	}
	return (false);
}

bool	handle_command(char *command)
{
	if (check_builtin(command) == true || check_external(command) == true)
		return (ft_printf("SUCCESS\n"), true);
	else
		return (ft_printf("THIS IS NOT A VALID COMMAND YOU KNOBHEAD\n"), false);
}

void	free_token_list(t_token *token)
{
	t_token	*current;
	t_token	*next;

	current = token;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	print_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		ft_printf("%s is of type %d on the index %d\n", current->str, current->type, current->index);
		current = current->next;
	}
}

int	token_type(char *strings)
{
	if (!ft_strncmp(strings, "<", 2))
		return (RE_INPUT);
	else if (!ft_strncmp(strings, ">", 2))
		return (RE_OUTPUT);
	else if (!ft_strncmp(strings, ">>", 3))
		return (APPEND);
	else if (!ft_strncmp(strings, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(strings, "<<", 3))
		return (HERE_DOC);
	else
		return (COMMAND);
	}

t_token	*handle_input(t_token *token, char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		token = tokenizer(strings[i], token_type(strings[i]), token);
		i++;
	}
	if (token->type == 0 && handle_command(strings[0]) == false)
		return (NULL);
	token_relativity(token);
	return (token);
}

void	print_lines(t_line *line)
{
	t_line	*current;
	int		i;

	current = line;
	while (current)
	{
		i = 0;
		ft_printf("COMMAND: ");
		while (current->command && current->command[i])
			ft_printf("%s ", current->command[i++]);
		
		i = 0;
		ft_printf("INFILE: ");
		while (current->infile && current->infile[i])
			ft_printf("%s ", current->infile[i++]);
		
		i = 0;
		ft_printf("DELIMITER: ");
		while (current->delimiter && current->delimiter[i])
			ft_printf("%s ", current->delimiter[i++]);
		
		ft_printf("INFILE OR DELIMITER: %d ", current->infile_or_delimiter);

		i = 0;
		ft_printf("OUTFILE: ");
		while (current->outfile && current->outfile[i])
			ft_printf("%s ", current->outfile[i++]);
		
		i = 0;
		ft_printf("APPEND: ");
		while (current->append && current->append[i])
			ft_printf("%s ", current->append[i++]);

		ft_printf("OUTFILE OR APPEND: %d ", current->outfile_or_append);		
		
		ft_printf("\n");
		current = current->next;
	}
}

void	parse_string(char *line)
{
	char	**strings;
	t_token	*token;
	t_line	*parsed_lines;

	if (ft_strncmp(line, "\0", 1) == 0)
		return ;
	token = NULL;
	parsed_lines = NULL;
	strings = ft_split(line, ' ');
	token = handle_input(token, strings);
	print_tokens(token);
	parsed_lines = structurize_line(token, parsed_lines);
	print_lines(parsed_lines);
//	free_matrix(strings);
//	free_token_list(token);
}
