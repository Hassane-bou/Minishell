/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:03:15 by rmouafik          #+#    #+#             */
/*   Updated: 2025/09/28 14:33:34 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_env **env_copy)
{
	t_env	*head;

	head = *env_copy;
	while (head)
	{
		printf("declare -x ");
		if (head->value == NULL)
			printf("%s\n", head->key);
		else
		{
			printf("%s=", head->key);
			printf("\"%s\"\n", head->value);
		}
		head = head->next;
	}
}

int	check_args(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (!ft_isalpha(str[i]) && str[i] != '_'))
			return (1);
		else if (i != 0 
			&& (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '='))
			return (1);
		i++;
	}
	return (0);
}

int	handle_export_value(t_help *var, char *item, t_env **env_copy)
{
	if (is_contain_equal(item))
		key_value_alloc(var, item);
	else
	{
		free(var->key);
		var->key = ft_strdup(item);
		var->value = get_env_value(env_copy, var->key);
	}
	return (0);
}

int	process_export_item(char *item, t_env **env_copy)
{
	t_help	var;

	var.export = 0;
	if (!item || item[0] == '\0')
		return (print_error(item), 1);
	var.ptr_value = ft_strchr(item, '=');
	var.value = var.ptr_value + 1;
	var.pos = var.ptr_value - item;
	var.key = ft_substr(item, 0, var.pos);
	if (check_args(var.key))
	{
		print_error(item);
		var.export = 1;
	}
	handle_export_value(&var, item, env_copy);
	if (!var.export)
		add_update_env(env_copy, var.key, var.value);
	free(var.key);
	return (var.export);
}

int	ft_export(char **arr, t_env **env_copy)
{
	int	i;
	int	status;

	if (!arr[1])
		return (print_export(env_copy), 0);
	i = 0;
	status = 0;
	while (arr[++i])
		if (process_export_item(arr[i], env_copy))
			status = 1;
	return (status);
}
