/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:37:49 by fmick             #+#    #+#             */
/*   Updated: 2025/03/03 11:37:03 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
1. readline() → Reads user input, allowing command-line editing.
2. add_history(input) → Adds the entered command to the history buffer.
3. Arrow Key Handling (Up/Down): Detect when the user presses arrow keys:

    Up Arrow (↑) → Navigate to the previous history entry.
    Down Arrow (↓) → Navigate to the next history entry.

4. rl_replace_line(history_entry, 0) → Replace the current input line with a previous command.
5. rl_on_new_line() → Move to a new line before displaying the updated command.
6. rl_redisplay() → Refresh and show the updated command
*/

void    ft_history(void)
{
    char    *input;
    int     i;

    i = 0;
    input = readline("");
    if (input[i] != '\0')
        {
            add_history(input);
        }
    /*    
    if (condition for arrow_up)
    {
        history = prev_history();
        if
        {
            rl_replace_line(history, 0);
            rl_on_new_line();
            rl_redisplay();
        }
    }
    else if (condition for arrow_down)
    {
        history = next_history();
        if
        {
            rl_replace_line(history, 0);
            rl_on_new_line();
            rl_redisplay();
        }
    }
    free (input);
    */
}
