/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntaxe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:00:42 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/27 12:49:07 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe1_syntaxe(char *input, int i)
{
	char	quote;
	int		j;

	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && !quote)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		if (!quote)
		{
			if (input[i] == '|' && input[i + 1] && input[i + 1] == '|')
				return (1);
			if (input[i] == '|')
			{
				j = i + 1;
				while (ft_isspace(input[j++]))
					if (input[j] == '|')
						return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_redirection1_syntaxe(char *input, int i)
{
	char	redirect;
	int		count;

	if (input[i] == '>' || input[i] == '<')
	{
		redirect = input[i];
		count = 0;
		while (input[i] == redirect)
		{
			count++;
			i++;
		}
		if (count > 2)
			return (1);
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '\0' || input[i] == '|' || input[i] == '>'
			|| input[i] == '<')
			return (1);
	}
	return (0);
}
