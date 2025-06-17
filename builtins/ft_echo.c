/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:51 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/17 11:28:59 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	ft_echo(char **arr, t_env *env_copy)
{
	int	i = 1;

	while (arr[i])
	{
		if (i == 1 && !ft_strcmp(arr[i], "-n"))
			i++;
		if (arr[i])
			printf("%s", arr[i]);
		if (arr[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (ft_strcmp(arr[1] , "-n"))
		printf("\n");
	return 0;
}
