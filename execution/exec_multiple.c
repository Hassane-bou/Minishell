/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:37:38 by rmouafik          #+#    #+#             */
/*   Updated: 2025/07/09 11:34:03 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void execute_multiple(t_cmd *cmd, t_env **env_copy)
{
	int	pipe_fd[2];
	int	pid;
	int	i;
	char **env_arr;

	env_arr = env_to_arr(*env_copy);
	i = cmd->pipe_count;
	while (cmd)
	{
		if (cmd->next != NULL)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit (1);
			}
		}
		pid = fork();
		if (pid == 0)
		{
			if (i == cmd->pipe_count)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				child_process(cmd, env_arr);
				close(pipe_fd[1]);
			}
			else if (cmd->next == NULL)
			{
				close(pipe_fd[1]);
				dup2(pipe_fd[0], STDIN_FILENO);
				child_process(cmd, env_arr);
				close(pipe_fd[0]);
			}
			else
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				dup2(pipe_fd[0], STDIN_FILENO);
				child_process(cmd, env_arr);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
		}
		// close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		i--;
		cmd = cmd->next;
	}
}