/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:06 by fmick             #+#    #+#             */
/*   Updated: 2025/03/06 12:36:06 by Barmyh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// relevant env
// HOME=/home/Barmyh
// PWD=/home/Barmyh/42-School/mini-shell
// OLDPWD=/home/Barmyh/42-School
// USER=Barmyh

//update var or add a new one

char	*ft_find_key(t_env	*env, char *key)
{
	t_env	*lst;

	lst = env;
	while(lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
			return lst->value;
		lst = lst->next;
	}
	return NULL;
}
int		ft_update_value(t_env *env, char *key, char *value)
{
	t_env *lst;
	t_env *new_var;

	lst = env;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			free(lst->value);
			lst->value = ft_strdup(value);
			return 0;
		}
		lst = lst->next;
	}
	new_var = malloc(sizeof(t_env));
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = NULL;
	lst->next = new_var;
	return 0;
}

static void	ft_go_to_dir(t_env *env, int av)
{
	char	*pwd;
	char	*oldpwd;
	char	*newpwd;
	int		i;

	pwd = ft_find_key(env, "PWD");

	// Save OLDPWD
	oldpwd = ft_strdup(pwd);
	ft_update_value(env, "OLDPWD", oldpwd);
	free(oldpwd);

	// cd ..
	if (av == 0)
	{
		i = ft_strlen(pwd);
		while (i > 0 && pwd[i] != '/')
			i--;
		if (i > 0)
			pwd[i] = '\0';
		newpwd = ft_strdup(pwd);
		ft_update_value(env, "PWD", newpwd);
		free(newpwd);
	}
	// cd -
	else if (av == 1)
	{
		oldpwd = ft_find_key(env, "OLDPWD");
		if (!oldpwd)
			return;
		pwd = ft_find_key(env, "PWD");
		ft_update_value(env, "PWD", oldpwd);
		ft_update_value(env, "OLDPWD", pwd);
		printf("%s\n", oldpwd);
	}
}

void	ft_cd(char **av, t_env *env)
{
	char	*home;

	home = ft_find_key(env, "HOME");
	if (av[1] == NULL || ft_strcmp(av[1], "~") == 0)
	{
		if (home)
			ft_update_value(env, "PWD", home);
		else
			return ;
	}
	else if (ft_strcmp(av[1], "..") == 0)
	{
		ft_go_to_dir(env, 0);
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		ft_go_to_dir(env, 1);
	}
	else
		ft_update_value(env, "PWD", av[1]);

	// cd /nonexistant: No such file or directory
	// cd /file: Not a directory
}
