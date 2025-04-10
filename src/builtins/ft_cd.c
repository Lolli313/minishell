/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakerblo <aakerblo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:06 by fmick             #+#    #+#             */
/*   Updated: 2025/04/10 16:14:02 by aakerblo         ###   ########.fr       */
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

static void	ft_cd_error(char *path, int error)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (error == 0)
		ft_putstr_fd("HOME not set\n", STDERR_FILENO);
	else if (error == 1)
		ft_putstr_fd("can't change directory\n", STDERR_FILENO);
	else if (error == 2)
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	else if (error == 3)
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
	return ;
}

static void	ft_update_pwd(t_env *env, char *newpath)
{
	char	*oldpwd;

	oldpwd = ft_find_key(env, "PWD");
	if (oldpwd)
		ft_update_value(env, "OLDPWD", oldpwd);
	ft_update_value(env, "PWD", newpath);
}

static char	*ft_handle_relative(char *pwd, char *path)
{
	size_t	len;
	char	*newpwd;

	len = ft_strlen(pwd) + ft_strlen(path) + 2;
	if (!(newpwd = malloc(len)))
		return (NULL);
	ft_strlcpy(newpwd, pwd, len);
	ft_strlcat(newpwd, "/", len);
	ft_strlcat(newpwd, path, len);
	return (newpwd);
}

static char *ft_get_newpwd(t_env *env, char *path)
{
	char	*pwd;
	char	*newpwd;

	pwd = ft_find_key(env, "PWD");
	newpwd = NULL;
	if (!pwd)
		pwd = "";

	if (path[0] == '/')
		newpwd = ft_strdup(path);
	else if (ft_strcmp(path, "..") == 0)
	{
		char *last_slash = ft_strrchr(pwd, '/');
		if (last_slash && last_slash != pwd)
			newpwd = ft_substr(pwd, 0, last_slash - pwd);
		else
			newpwd = ft_strdup("/");
	}
	else
		ft_handle_relative(pwd, path);
	return (newpwd);
}

static void	ft_change_dir(t_env *env, char *path, int print_dir)
{
	char	*newpwd;

	if (chdir(path) == 0)
	{
		newpwd = ft_get_newpwd(env, path);
		if (print_dir)
			ft_printf("%s\n", newpwd);
		ft_update_pwd(env, newpwd);
		free(newpwd);
	}
	else
		ft_cd_error(path, 3);
}

void	ft_cd(char **av, t_env *env)
{
	char	*target;
	int		print_dir;

	print_dir = false;
	if (!av[1] || ft_strcmp(av[1], "~") == 0)
	{
		target = ft_find_key(env, "HOME");
		if (!target)
			ft_cd_error(NULL, 0);
	}
	else if (ft_strcmp(av[1], "-") == 0)
	{
		target = ft_find_key(env, "OLDPWD");
		print_dir = true;
		if (!target)
			ft_cd_error("OLDPWD", 1);
	}
	else if (av[2] != NULL)
	{
		ft_cd_error(NULL, 2);
		return ;
	}
	else
		target = av[1];
	ft_change_dir(env, target, print_dir);
}
