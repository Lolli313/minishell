/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmick <fmick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:06 by fmick             #+#    #+#             */
/*   Updated: 2025/05/05 10:17:11 by fmick            ###   ########.fr       */
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
	if(pwd[ft_strlen(pwd) - 1] != '/')
		ft_strlcat(newpwd, "/", len);
	ft_strlcat(newpwd, path, len);
	return (newpwd);
}

static char	*ft_get_newpwd(char *oldpwd, char *path)
{
	char	*newpwd;
	char	*last_slash;

	if (ft_strcmp(path, ".") == 0)
		return (ft_strdup(oldpwd));
	else if (path[0] == '/')
		return (ft_strdup(path));
	else if (ft_strcmp(path, "..") == 0)
	{
		last_slash = ft_strrchr(oldpwd, '/');
		if (last_slash && last_slash != oldpwd)
			return (ft_substr(oldpwd, 0, last_slash - oldpwd));
		return (ft_strdup("/"));
	}
	else
		newpwd = ft_handle_relative(oldpwd, path);
	return (newpwd);
}

static int	ft_change_dir(t_env *env, char *path, int print_dir)
{
	char	*newpwd;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		free(oldpwd);
		return (ft_cd_error(path, 3));
	}
	newpwd = ft_get_newpwd(oldpwd, path);
	if (!newpwd)
	{
		free(oldpwd);
		return (ft_cd_error(path, 3));
	}
	if (print_dir)
		ft_printf("%s\n", newpwd);
	ft_update_value(env, "OLDPWD", oldpwd);
	ft_update_value(env, "PWD", newpwd);
	free(oldpwd);
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
