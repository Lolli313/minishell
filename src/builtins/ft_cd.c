/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Barmyh <Barmyh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:06 by fmick             #+#    #+#             */
/*   Updated: 2025/04/06 14:41:53 by Barmyh           ###   ########.fr       */
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
			break;
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

static void	ft_update_pwd(t_env *env)
{
	char cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_update_value(env, "OLDPWD", ft_find_key(env, "PWD"));
		ft_update_value(env, "PWD", cwd);
	}
}

static void	ft_change_dir(t_env *env, char *path, int print_dir)
{
	if (chdir(path) == 0)
	{
	if (print_dir == true)
		ft_printf("%s\n", path);
	ft_update_pwd(env);
	}
	else
		ft_cd_error(NULL, 3);
}

void	ft_cd(char **av, t_env *env)
{
	char *target;
	int print_dir = false;

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
