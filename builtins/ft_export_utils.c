/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:09:38 by rmouafik          #+#    #+#             */
/*   Updated: 2025/09/28 14:29:05 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	key_value_alloc(t_help *var, char *str)
{
	var->ptr_value = ft_strchr(str, '=');
	var->value = var->ptr_value + 1;
	var->pos = var->ptr_value - str;
	free(var->key);
	var->key = ft_substr(str, 0, var->pos);
}

int	is_contain_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	add_update_env(t_env **env_copy, char *key, char *value)
{
	t_env	*head;
	t_env	*new_node;

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
