/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:54 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/14 13:35:42 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*get_env_value(t_env **env_copy, char *key)
{
	t_env	*head;
	
	head = *env_copy;
	while (head->value)
	{
		if (!ft_strcmp(head->key, key))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

void	add_env(t_env *env_copy, char *key, char *value)
{
	t_env *new_node;

	new_node = env_copy;
	new_node = malloc(sizeof(t_env));
	while (new_node->value)
		new_node = new_node->next;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	env_add_back(&env_copy, new_node);
}

int	ft_cd(char *path, t_env **env_copy)
{
	char *old_path;

	old_path = get_env_value(env_copy, "PWD");
	if (!ft_strcmp(path, "-"))
	{
		if (get_env_value(env_copy, "OLDPWD") == NULL)
			return (printf("minishell: cd: OLDPWD not set"), 1);
		chdir(old_path);
		printf("%s\n", old_path);
		return 0;
	}
	chdir(path);
	// if (get_env_value(env_copy, "OLDPWD") != NULL)
		add_env(*env_copy, "OLDPWD", old_path);
	return 0;
}