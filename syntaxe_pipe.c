/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:39:16 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/16 15:52:50 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_pipe1_syntaxe(char *input,int i)
{
    int j;
    while (ft_isspace(input[i]))
			i++;
    if (input[i] == '|' && input[i + 1] && input[i + 1] == '|')
    	return (1);
    if (input[i] == '|')
    {
	    j = i + 1;
    	while (ft_isspace(input[j]))
            j++;
    	if (input[j] == '|')
    		return (1);
	}
    return 0;
}

int	check_pipe_syntaxe(char *input)
{
	int	i;
	int	end_input;
	int	j;

    j = 0;
	end_input = ft_strlen(input) - 1;
	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '|')
		return (1);
	while (end_input >= 0 && ft_isspace(input[end_input]))
		end_input--;
	if (input[end_input] == '|')
		return (1);
	while (input[i])
	{
		if(check_pipe1_syntaxe(input,i))
            return 1;
		i++;
	}
	return (0);
}
