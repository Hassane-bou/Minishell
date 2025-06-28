/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:37:38 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/28 13:18:52 by rmouafik         ###   ########.fr       */
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

void	ft_execute(t_cmd *cmd, t_env **env_copy)
{
	
}
