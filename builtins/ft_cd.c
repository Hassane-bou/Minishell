/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:54 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/19 13:28:57 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*get_env_value(t_env **env_copy, char *key)
{
	t_env	*head;
	
	head = *env_copy;
	while (head)
	{
		if (!ft_strcmp(head->key, key))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

void	add_update_env(t_env **env_copy, char *key, char *value)
{
	t_env *head;
	t_env *new_node;

	head = *env_copy;
	while (head)
	{
		if (!ft_strcmp(head->key, key))
		{
			free(head->value);
			head->value = ft_strdup(value);
			return ;
		}
		head = head->next;
	}
	new_node = *env_copy;
	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	env_add_back(env_copy, new_node);
}

int	ft_cd(char *path, t_env **env_copy)
{
	char *old_path;
	char *pwd;
	char *home;

	pwd = getcwd(NULL, 0);
	home = get_env_value(env_copy, "HOME");
	if (path == NULL || !ft_strcmp(path, "~"))
	{
		if (get_env_value(env_copy, "HOME") == NULL)
			return (printf("minishell: cd: HOME not set\n"), 1);
		old_path = getcwd(NULL, 0);
		chdir(home);
	}
	if (!ft_strcmp(path, "-"))
	{
		if (get_env_value(env_copy, "OLDPWD") == NULL)
			return (printf("minishell: cd: OLDPWD not set\n"), 1);
		old_path = get_env_value(env_copy, "OLDPWD");
		pwd = getcwd(NULL, 0);
		if (chdir(old_path) == 0)
		{
			printf("%s\n", old_path);
		}
	}
	if (chdir(path) != 0 && ft_strcmp(path, "-") && ft_strcmp(path, "~") && path != NULL)
		return (printf("minishell: cd: %s: No such file or directory\n", path), 1);
	if (old_path == NULL)
		add_update_env(env_copy, "OLDPWD", old_path);
	add_update_env(env_copy, "OLDPWD", pwd);
	add_update_env(env_copy, "PWD", getcwd(NULL, 0));
	return 0;
}
