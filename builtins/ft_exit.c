/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:02:49 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/24 13:32:30 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"
# include <limits.h>

int	check_args(char **arr)
{
	int	i;
	int	j;

	i = 1;
	while (arr[i])
	{
		j = 0;
		while (ft_isdigit(arr[i][j]))
			j++;
		i++;
	}
	return (i - 1);
}

int	check_long(const char *str)
{
	unsigned long long	result;
	unsigned long long	limit;
	int					sign;
	int					i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (sign < 0)
		limit = LLONG_MIN;
	else
		limit = LLONG_MAX;
	while (ft_isdigit(str[i]))
	{
		if (result > (limit - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

int ft_exit(char **arr, t_env **env_copy)
{
	int	i;

	i = 1;
	printf("exit\n");
	if (check_args(arr) != 1)
		return (printf("minishell: exit: too many arguments\n"), 1);
	if (arr[1] == NULL)
		exit(0);
	else if (arr[1] != NULL)
	{
		if (!check_long(arr[1]))
			printf("minishell: exit: %s: numeric argument required\n", arr[1]);
		exit(ft_atoi(arr[1]));
	}
	return 0;
}
