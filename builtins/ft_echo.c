/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:51 by rmouafik          #+#    #+#             */
/*   Updated: 2025/09/28 12:29:41 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_echo(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **arr)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	while (arr[i] && check_echo(arr[i]))
	{
		new_line = 1;
		i++;
	}
	while (arr[i])
	{
		if (arr[i])
			ft_putstr_fd(arr[i], 1);
		if (arr[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (new_line == 0)
		write(1, "\n", 1);
	return (0);
}
