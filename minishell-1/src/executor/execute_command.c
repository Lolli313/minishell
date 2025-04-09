#include "minishell.h"

static void execute_single_command(t_command *cmd, t_env *env)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (cmd->input_fd != 0)
            dup2(cmd->input_fd, STDIN_FILENO);
        if (cmd->output_fd != 1)
            dup2(cmd->output_fd, STDOUT_FILENO);
        execve(cmd->path, cmd->args, env_to_string(env));
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            cmd->exit_status = WEXITSTATUS(status);
    }
}

void execute_commands(t_command_list *commands, t_env *env)
{
    t_command *current;

    current = commands->head;
    while (current)
    {
        execute_single_command(current, env);
        current = current->next;
    }
}