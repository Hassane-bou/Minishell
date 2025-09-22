/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntaxe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:30:19 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/22 09:36:34 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *input)
{
	int		i;
	char	quote_char;

	i = 0;
	quote_char = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && !quote_char)
			quote_char = input[i];
		else if (input[i] == quote_char)
			quote_char = 0;
		i++;
	}
	if (quote_char)
		return (1);
	else
		return (0);
}

int	check_pipe_syntaxe(char *input)
{
	int	i;
	int	len;
	int	end_input;

	i = 0;
	len = ft_strlen(input);
	end_input = len - 1;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '|')
		return (1);
	while (end_input >= 0 && ft_isspace(input[end_input]))
		end_input--;
	if (input[end_input] == '|')
		return (1);
	if (check_pipe1_syntaxe(input, i))
		return (1);
	return (0);
}

int	check_redirection_syntaxe(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '"' || input[i] == '\'') && !quote)
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
				quote = 0;
			i++;
			continue ;
		}
		if (check_redirection1_syntaxe(input, i))
			return (1);
		else
			i++;
	}
	return (0);
}

int	check_all_syntaxe(char *input)
{
	if (check_pipe_syntaxe(input))
	{
		printf("syntax error near unexpected token `|'\n");
		free(input);
		return (1);
	}
	if (check_quotes(input))
	{
		printf("erreur quotes\n");
		free(input);
		return (1);
	}
	if (check_redirection_syntaxe(input))
	{
		printf("syntax error near unexpected token `newline'\n");
		free(input);
		return (1);
	}
	return (0);
}
