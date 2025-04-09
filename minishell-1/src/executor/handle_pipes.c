#include "minishell.h"

void	handle_pipes(t_command *commands, int num_commands)
{
	int		i;
	int		pipe_fd[2];
	int		prev_fd;

	prev_fd = -1;
	i = 0;
	while (i < num_commands)
	{
		if (i < num_commands - 1)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		if (fork() == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i < num_commands - 1)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			execute_command(commands[i]);
			exit(EXIT_SUCCESS);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (i < num_commands - 1)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		i++;
	}
	while (wait(NULL) > 0);
}