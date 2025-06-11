/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:35:46 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/11 11:29:06 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[], char **envp)
{
	int		i;
	int		pos;
	t_env	**env_copy;
	char	*str_value;

	i = 0;
	while (envp[i])
		i++;
	env_copy = malloc(sizeof(t_env *) * i);
	i = 0;
	while (envp[i])
	{
		env_copy[i] = malloc(sizeof(t_env));
		str_value = ft_strchr(envp[i], '=');
		pos = str_value - envp[i];
		env_copy[i]->key = ft_substr(envp[i], 0, pos);
		env_copy[i]->value = ft_strdup(str_value + 1);
		printf("%s=%s\n", env_copy[i]->key, env_copy[i]->value);
		i++;
	}
}
