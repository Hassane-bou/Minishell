/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:37:38 by rmouafik          #+#    #+#             */
/*   Updated: 2025/09/20 12:52:39 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_contain_slash(char *cmd)
{
	int	i;

	i = 0;
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
	char	*tmp;
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

int in_redirect_buil(t_cmd *cmd)
{
	int				fd;
	t_redriection	*tmp;

	tmp = cmd->red;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			fd = open(tmp->file_or_delim, O_RDONLY, 0777);
			if (fd < 0)
				return (perror("infile error!"), -1);
			if (dup2(fd, STDIN_FILENO) == -1)
			{
				perror("dup failed!");
				return (-1);
			}
			close(fd);
		}
		tmp = tmp->next;
	}
	return (1);
}

int out_redirect_buil(t_cmd *cmd)
{
	int fd;
	t_redriection *tmp;

	tmp = cmd->red;
	while (tmp)
	{
		if (tmp->type == APPEND || tmp->type == REDIR_OUT)
		{
			if (tmp->type == APPEND)
				fd = open(tmp->file_or_delim, O_CREAT | O_RDWR | O_APPEND, 0777);
			else
				fd = open(tmp->file_or_delim, O_CREAT | O_RDWR | O_TRUNC, 0777);
			if (fd < 0)
				return (perror("outfile error"), -1);
			if ((tmp->next == NULL) || (tmp->next && tmp->next->type != APPEND && tmp->next->type != REDIR_OUT))
			{
				if (dup2(fd, STDOUT_FILENO) == -1)
					return (perror("dup failed!"), -1);
				close(fd);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int ft_redirect_buil(t_cmd *cmd)
{
	if (in_redirect_buil(cmd) == -1)
		return (-1);
	if (out_redirect_buil(cmd) == -1)
		return (-1);
	return (0);
}

void child_process(t_cmd *cmd, char **env_arr, t_env **env_copy)
{
	char	*exact_path;
	char	**paths;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_redirect(cmd);
	if (!cmd->args[0] || !cmd->args)
		exit(0);
	paths = get_path(env_arr, cmd->args[0]);
	if (!paths)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_cmd_list(cmd);
		exit(1);
	}
	exact_path = check_path(paths);
	if (is_contain_slash(cmd->args[0]))
	{
		execve(cmd->args[0], cmd->args, env_arr);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_args(paths);
		free_cmd_list(cmd);
		(*env_copy)->exit_status = 127;
		exit(127);
	}
	execve(exact_path, cmd->args, env_arr);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_args(paths);
	free_cmd_list(cmd);
	(*env_copy)->exit_status = 127;
	exit(127);
}

void cmd_built(t_cmd *cmd, t_env **env_copy, int *status)
{
	int save_in;
	int save_out;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (ft_redirect_buil(cmd) == -1)
	{
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		close(save_in);
		close(save_out);
		return ;
	}
	*status = run_builtin(cmd, env_copy);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
	return ;
}

void	execute_one(t_cmd *cmd, t_env **env_copy)
{
	pid_t	pid;
	char	**env_arr;
	int		status;

	env_arr = env_to_arr(*env_copy);
	if (is_builtin(cmd))
	{
		cmd_built(cmd, env_copy, &status);
		(*env_copy)->exit_status = status;
		free_args(env_arr);
		return ;
	}
	pid = fork();
	if (pid == 0)
		child_process(cmd, env_arr, env_copy);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status))
		(*env_copy)->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		(*env_copy)->exit_status = 128 + WTERMSIG(status);
    	if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit", 2);
	}
	free_args(env_arr);
}

char *expand_string_her(char *word, char **envp, t_env *env_head)
{
    int     i;
    int     start;
    char    *var_name;
    char    *value;
    char    *tmp;
    char    *res;

	i = 0;
	start = 0;
	res = ft_strdup("");
    if (!word)
        return (ft_strdup(""));
    while (word[i])
    {
        if (word[i] == '$')
        {
            i++;
            if (word[i] == '?')
            {
                char *str = ft_itoa(env_head->exit_status);
                tmp = ft_strjoin(res, str);
                free(res);
                free(str);
                res = tmp;
                i++;
                continue;
            }
            start = i;
            while (word[i] && is_valid_env_char(word[i]))
                i++;
            var_name = ft_substr(word, start, i - start);
            value = get_env_value_par(var_name, envp);
            free(var_name);
            if (value)
            {
                tmp = ft_strjoin(res, value);
                free(res);
                res = tmp;
            }
        }
        else
        {
            tmp = ft_strjoin_char(res, word[i]);
            free(res);
            res = tmp;
            i++;
        }
    }
    return (res);
}

void	run_herdoc(t_cmd *cmd, t_redriection *tmp, int fd, t_env **env_copy, t_token *res)
{
	char *line;
	char **env_arr;

	env_arr = env_to_arr(*env_copy);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (!ft_strcmp(line, tmp->file_or_delim))
		{
			free(line);
			break ;
		}
		if (!res->quoted)
			line = expand_string_her(line, env_arr, *env_copy);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	ft_herdoc(t_cmd *cmd, t_env **env_copy, t_token *res)
{
	t_redriection	*tmp;
	int 			pid;
	int				heredoc_fd[2];
	int				status;

	tmp = cmd->red;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (pipe(heredoc_fd) == -1)
			{
				perror("pipe");
				exit(1);
			}
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_IGN);
				close(heredoc_fd[0]);
				run_herdoc(cmd, tmp, heredoc_fd[1], env_copy, res);
				close(heredoc_fd[1]);
				exit(0);
			}
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			waitpid(pid, &status, 0);
			setup_signals();
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			{
				(*env_copy)->exit_status = 130;
				write(1, "\n", 1);
				close(heredoc_fd[0]);
				close(heredoc_fd[1]);
				return (-1);
			}
			close(heredoc_fd[1]);
			cmd->herdoc_fd = heredoc_fd[0];
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_execute(t_cmd *cmd, t_env **env_copy, char *input, t_token *res)
{
	t_cmd *current;

	current = cmd;
	while (current)
	{
		if (ft_herdoc(current, env_copy, res) == -1)
			return (0);
		current = current->next;
	}
	if (cmd->next == NULL)
		execute_one(cmd, env_copy);
	else
		execute_multiple(cmd, env_copy);
	return (0);
}
