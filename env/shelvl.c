/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shelvl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:04:55 by rmouafik          #+#    #+#             */
/*   Updated: 2025/09/24 09:47:01 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_shelvl(t_env *env_list)
{
	int	lvl;

	while (env_list)
	{
		if (ft_strncmp(env_list->key, "SHLVL", 6) == 0)
		{
			free(env_list->value);
			lvl = ft_atoi(env_list->value);
			if (lvl >= 1000)
			{
				ft_putstr_fd("minishell: warning: shell level (", 2);
				ft_putstr_fd(env_list->value, 2);
				ft_putstr_fd(") too high, resetting to 1\n", 2);
				lvl = 0;
			}
			lvl++;
			env_list->value = ft_itoa(lvl); 
		}
		env_list = env_list->next;
	}
}
