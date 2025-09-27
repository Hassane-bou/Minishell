/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:51 by rmouafik          #+#    #+#             */
/*   Updated: 2025/09/27 12:52:39 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	check_echo(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!ft_strcmp(&str[0], "-") && !ft_strcmp(&str[i], "n"))
// 			return 1;
// 		i++;
// 	}
// 	return 0;
// }

int	ft_echo(char **arr)
{
	int	i;

	i = 1;
	while (arr[i])
	{
		if (i == 1 && !ft_strcmp(arr[i], "-n"))
			i++;
		if (arr[i])
			ft_putstr_fd(arr[i], 1);
		if (arr[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (ft_strcmp(arr[1], "-n"))
		write(1, "\n", 1);
	return (0);
}
