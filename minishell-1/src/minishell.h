// filepath: /minishell/minishell/src/minishell.h
#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Structure for environment variables
typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;

// Function declarations
t_env *ft_add_env_node(char *key, char *value);
void free_matrix(char **matrix);
int ft_env_exists(t_env *env, char *key, char *value);
t_env *ft_init_export_env_(char **envp);
int ft_export_env(t_mini *mini, char **str);
int ft_export(t_env *env, char **str);
void ft_putstr_fd(char *s, int fd);
int export_validity(char *key);
void ft_cd(char **args);
void ft_echo(char **args);
void ft_env(t_env *env);
void ft_exit(char **args);
void ft_pwd(void);
void ft_unset(t_env *env, char **args);
void execute_command(char **args);
void handle_pipes(char **args);
void redirections(char **args);
void parse_input(char *input);
void tokenize(char *input);
void validate_syntax(char *input);

#endif // MINISHELL_H