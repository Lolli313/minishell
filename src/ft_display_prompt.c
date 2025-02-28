/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:33:19 by fmick             #+#    #+#             */
/*   Updated: 2025/02/28 10:35:54 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Display prompt
// PS0 is displayed after each command, before any output
// PS1 is the primary prompt which is displayed before each command, thus it is the one most people customize.

// PS2 is the secondary prompt displayed when a command needs more input (e.g. a multi-line command).

// PS3 is not very commonly used. It is the prompt displayed for Bash's select built-in which displays interactive menus. Unlike the other prompts, it does not expand Bash escape sequences. Usually you would customize it in the script where the select is used rather than in your .bashrc.

// PS4 is also not commonly used. It is displayed when debugging bash scripts to indicate levels of indirection. The first character is repeated to indicate deeper levels.
