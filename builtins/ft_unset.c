/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:37:35 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/17 13:20:51 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	is_valid(char *str)
{
	int	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return 1;
		i++;
	}
	return 0;
}

int	check_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && !ft_isdigit(str[i]) && ft_isalpha(str[i]))
			return 1;
		// if (!ft_isdigit(str[i]) || !ft_isalpha(str[i]))
		// 	return 1;
		i++;
	}
	return 0;
}

int	ft_unset(char **arr, t_env **env_copy)
{
	int i = 1;
	while (arr[i])
	{
		if (!check_valid(arr[i]))
			return (printf("minishell: unset: `%s': not a valid identifier\n", arr[i]), 1);
		i++;
	}
	return 0;
}
