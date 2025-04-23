/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:06 by fmick             #+#    #+#             */
/*   Updated: 2025/04/23 09:33:37 by fmick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	new_var = malloc(sizeof(t_env));
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = NULL;
	if (lst)
		lst->next = new_var;
	else
		env = new_var;
	return (0);
}

static char	*ft_handle_relative(char *pwd, char *path)
{
	size_t	len;
	char	*newpwd;

	len = ft_strlen(pwd) + ft_strlen(path) + 2;
	newpwd = malloc(len);
	if (!(newpwd))
		return (NULL);
	ft_strlcpy(newpwd, pwd, len);
	ft_strlcat(newpwd, "/", len);
	ft_strlcat(newpwd, path, len);
	return (newpwd);
}

static char	*ft_get_newpwd(t_env *env, char *path)
{
	char	*pwd;
	char	*newpwd;
	char	*last_slash;

	pwd = ft_find_key(env, "PWD");
	newpwd = NULL;
	if (!pwd)
		pwd = "";
	if (ft_strcmp(path, ".") == 0)
		newpwd = ft_strdup(pwd);
	else if (path[0] == '/')
		newpwd = ft_strdup(path);
	else if (ft_strcmp(path, "..") == 0)
	{
		last_slash = ft_strrchr(pwd, '/');
		if (last_slash && last_slash != pwd)
			newpwd = ft_substr(pwd, 0, last_slash - pwd);
		else
			newpwd = ft_strdup("/");
	}
	else
		newpwd = ft_handle_relative(pwd, path);
	return (newpwd);
}

static int	ft_change_dir(t_env *env, char *path, int print_dir)
{
	char	*newpwd;
	char	*oldpwd;

	if (chdir(path) != 0)
		return (ft_cd_error(path, 3));
	newpwd = ft_get_newpwd(env, path);
	if (!newpwd)
		return (ft_cd_error(path, 3));
	if (print_dir)
		ft_printf("%s\n", newpwd);
	oldpwd = ft_find_key(env, "PWD");
	if (oldpwd)
		ft_update_value(env, "OLDPWD", oldpwd);
	ft_update_value(env, "PWD", newpwd);
	free(newpwd);
	return (0);
}

int	ft_cd(char **av, t_env *env)
{
	char	*target;
	int		print_dir;

	print_dir = false;
	if (!av[1] || ft_strcmp(av[1], "~") == 0)
	{
		target = ft_find_key(env, "HOME");
		if (!target)
			return (ft_cd_error(NULL, 0));
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		target = ft_find_key(env, "OLDPWD");
		print_dir = true;
		if (!target)
			return (ft_cd_error("OLDPWD", 1));
	}
	else if (av[2] != NULL)
	{
		return (ft_cd_error(NULL, 2));
	}
	else
		target = av[1];
	return (ft_change_dir(env, target, print_dir));
}
