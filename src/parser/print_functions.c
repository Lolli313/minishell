/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:08:12 by aakerblo          #+#    #+#             */
/*   Updated: 2025/03/29 11:51:07 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		ft_printf("%s is of type %d on the index %d\n", current->str,
			current->type, current->index);
		current = current->next;
	}
}

void	print_lines(t_line *line)
{
	t_line	*current;
	t_re	*temp_re;
	int		i;

	current = line;
	while (current)
	{
		i = 0;
		ft_printf("COMMAND: ");
		while (current->command && current->command[i])
			ft_printf("%s ", current->command[i++]);
		i = 0;
		ft_printf("\nREDIRECTS: ");
		temp_re = current->redirect;
		while (temp_re)
		{
			ft_printf("%s ", temp_re->str);
			ft_printf("is type %d, ", temp_re->type);
			ft_printf("\n");
			temp_re = temp_re->next;
		}
		ft_printf("\n");
		current = current->next;
	}
}
