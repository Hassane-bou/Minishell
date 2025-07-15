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

#include "../minishell.h"

int		is_contain_slash(char *cmd)
{
	int i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return 1;
		i++;
	}
	return 0;
}
char	**get_path(char **envp, char *cmd)
{
	char	*str;
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			str = envp[i] + 5;
			arr = ft_split(str, ':');
			while (arr[j])
			{
				arr[j] = ft_strjoin(arr[j], "/");
				arr[j] = ft_strjoin(arr[j], cmd);
				j++;
			}
			return (arr);
		}
		i++;
	}
	return (NULL);
}

char	*check_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (access(path[i], F_OK | X_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}

void in_redirect(t_cmd *cmd)
{
	int fd;

	fd = open(cmd->infile, O_RDONLY, 0777);
	if (fd < 0)
		perror("infile error!");
	if (dup2(fd, 0) == -1)
	{
		perror("dup failed!");
		exit(1);
	}
	close(fd);
}

void out_redirect(t_cmd *cmd)
{
	int fd;
	int	i;

	i = 0;
	while (cmd->outfile[i])
	{

		if (cmd->append)
			fd = open(cmd->outfile[i], O_CREAT | O_RDWR | O_APPEND, 0777);
		else
			fd = open(cmd->outfile[i], O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd < 0)
		{
			perror("outfile error");
			exit(1);
		}
		if (cmd->outfile[i + 1] == NULL)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup failed!");
				exit(1);
			}
			close(fd);
		}
		i++;
	}
}

void child_process(t_cmd *cmd, char **env_arr)
{
	char	*exact_path;
	char	**paths;

	if (cmd->infile)
		in_redirect(cmd);
	if (cmd->outfile)
		out_redirect(cmd);
	if (!cmd->args[0] || !cmd->args)
		exit(0);
	paths = get_path(env_arr, cmd->args[0]);
	if (!paths)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	exact_path = check_path(paths);
	if (is_contain_slash(cmd->args[0]))
	{
		execve(cmd->args[0], cmd->args, env_arr);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(exact_path, cmd->args, env_arr);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void execute_one(t_cmd *cmd, t_env **env_copy)
{
	pid_t	pid;

	char	**env_arr;
	int		status;

	env_arr = env_to_arr(*env_copy);
	if (is_builtin(cmd, env_copy))
		return (run_builtin(cmd, env_copy));
	pid = fork();
	if (pid == 0)
		child_process(cmd, env_arr);
	waitpid(pid, &status, 0);
	// if (WIFEXITED(status))
	// 	(*env_copy)->status = WEXITSTATUS(status);
	// else if (WIFSIGNALED(status) && WIFEXITED(status))
	// {
	// 	(*env_copy)->status = WTERMSIG(status) + 128;
	// }
}

int	ft_execute(t_cmd *cmd, t_env **env_copy, char *input)
{
	if (!cmd->next)
		execute_one(cmd, env_copy);
	return 0;
}
