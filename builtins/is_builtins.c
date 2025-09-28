/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:50:42 by rmouafik          #+#    #+#             */
/*   Updated: 2025/09/28 12:55:53 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return (1);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "env") || !ft_strcmp(cmd->args[0], "ENV"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "pwd") || !ft_strcmp(cmd->args[0], "PWD"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "echo") || !ft_strcmp(cmd->args[0], "ECHO"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "export"))
		return (1);
	return (0);
}

int	run_builtin(t_cmd *cmd, t_env **env_copy)
{
	if (!ft_strcmp(cmd->args[0], "env") || !ft_strcmp(cmd->args[0], "ENV"))
		return (ft_env(*env_copy));
	if (!ft_strcmp(cmd->args[0], "pwd") || !ft_strcmp(cmd->args[0], "PWD"))
		return (ft_pwd(*env_copy));
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd->args[1], env_copy));
	if (!ft_strcmp(cmd->args[0], "echo") || !ft_strcmp(cmd->args[0], "ECHO"))
		return (ft_echo(cmd->args));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(cmd->args, env_copy));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd->args, env_copy, cmd));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(cmd->args, env_copy));
	return (1);
}

char	**env_to_arr(t_env *env_head)
{
	char	**env_arr;
	t_env	*tmp;
	char	*temp;
	t_help	var;

	var.i = 0;
	var.start = 0;
	tmp = env_head;
	while (tmp)
	{
		var.start++;
		tmp = tmp->next;
	}
	env_arr = malloc(sizeof(char *) * (var.start + 1));
	if (!env_arr)
		return (NULL);
	while (env_head)
	{
		temp = ft_strjoin(env_head->key, "=");
		env_arr[var.i] = ft_strjoin(temp, env_head->value);
		free(temp);
		var.i++;
		env_head = env_head->next;
	}
	return (env_arr[var.i] = NULL, env_arr);
}
