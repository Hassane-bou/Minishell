/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:51 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/28 09:57:38 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **arr, t_env *env_copy)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (i == 0 && !ft_strcmp(arr[i], "-n"))
			i++;
		if (arr[i])
			printf("%s", arr[i]);
		if (arr[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (ft_strcmp(arr[0], "-n"))
		printf("\n");
	return (0);
}
