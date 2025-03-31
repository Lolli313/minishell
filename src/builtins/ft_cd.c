/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:06 by fmick             #+#    #+#             */
/*   Updated: 2025/03/31 08:14:57 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// relevant env
// HOME=/home/Barmyh
// PWD=/home/Barmyh/42-School/mini-shell
// OLDPWD=/home/Barmyh/42-School
// USER=Barmyh

// update var or add a new one

int	ft_update_value(t_env *env, char *key, char *value)
{
	t_env	*lst;
	t_env	*new_var;

	lst = env;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			free(lst->value);
			lst->value = ft_strdup(value);
			return (0);
		}
		lst = lst->next;
	}
	new_var = malloc(sizeof(t_env));
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = NULL;
	lst->next = new_var;
	return (0);
}

static void	ft_go_to_dir(t_env *env, int av)
{
	char	*pwd;
	char	*oldpwd;
	char	*newpwd;
	int		i;

	pwd = ft_strdup(ft_find_key(env, "PWD"));
	oldpwd = ft_strdup(ft_find_key(env, "OLDPWD"));
	// cd ".."
	if (av == 0)
	{
		ft_update_value(env, "OLDPWD", pwd);
		i = ft_strlen(pwd);
		while (i > 0 && pwd[i] != '/')
			i--;
		if (i > 0)
			pwd[i] = '\0';
		newpwd = ft_strdup(pwd);
		ft_update_value(env, "PWD", newpwd);
		free(newpwd);
	}
	// cd "-"
	else if (av == 1)
	{
		ft_update_value(env, "OLDPWD", pwd);
		newpwd = ft_strdup(oldpwd);
		ft_update_value(env, "PWD", newpwd);
		free(newpwd);
	}
	free(pwd);
	free(oldpwd);
}

void	ft_cd(char **av, t_env *env)
{
	char	*home;

	home = ft_find_key(env, "HOME");
	if (av[1] == NULL || ft_strncmp(av[1], "~", 2) == 0)
	{
		if (home)
			ft_update_value(env, "PWD", home);
	}
	else if (ft_strncmp(av[1], "..", 3) == 0)
		ft_go_to_dir(env, 0);
	else if (ft_strncmp(av[1], "-", 2) == 0)
		ft_go_to_dir(env, 1);
	else if (av[1][0] == '/')
	 {
		if (access(av[1], F_OK) == 0)
			ft_update_value(env, "PWD", av[1]);
	 }
	else
		ft_update_value(env, "PWD", av[1]);
}
