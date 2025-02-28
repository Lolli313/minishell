/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:37:49 by fmick             #+#    #+#             */
/*   Updated: 2025/02/28 10:38:59 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*

Where is Bash history stored?

By default, history stores commands in RAM until you log out of the terminal. Once you log out, commands are written to disk in the ~/.bash_history file. The history buffer is limited to 1,000 command entries and the history file is limited to 2,000 entries.

You can modify the default behavior of the history command by setting environment variables, which we'll review in more detail shortly.

*/
