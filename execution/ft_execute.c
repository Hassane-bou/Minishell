/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:37:38 by rmouafik          #+#    #+#             */
/*   Updated: 2025/07/02 11:17:05 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void execute_one(t_cmd *cmd, t_env **env_copy)
{
	int		pid;
	char	*exact_path;
	char	**paths;
	char	**env_arr;

	env_arr = env_to_arr(*env_copy);
	if (is_builtin(cmd, env_copy))
		run_builtin(cmd, env_copy);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			paths = get_path(env_arr, cmd->cmd);
			exact_path = check_path(paths);
			if (execve(exact_path, cmd->args, env_arr) == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd->cmd, 2);
				ft_putstr_fd(": command not found\n", 2);
				exit(1);
			}
		}
		waitpid(pid, NULL, 0);
	}
}

int	ft_execute(t_cmd *cmd, t_env **env_copy, char *input)
{
	if (!cmd->next)
		execute_one(cmd, env_copy);
	return 0;
}
