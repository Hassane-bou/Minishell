/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:45:30 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/23 11:12:16 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_isspace(int c)
{
    return(c == 32  || (c >= 9 && c <= 13));
}

void	initilisation(t_cmd *cmd)
{
	cmd->quoted_del = 0;
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->red = NULL;
}

int	count_word_in_token(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			count++;
		token = token->next;
	}
	return (count);
}

t_redriection	*new_red(t_type type, char *file)
{
	t_redriection	*red;

	red = malloc(sizeof(t_redriection));
	if (!red)
		return (NULL);
	red->file_or_delim = ft_strdup(file);
	red->type = type;
	red->next = NULL;
	return (red);
}

void	add_red(t_type type, t_cmd *cmd, char *file)
{
	t_redriection	*red;
	t_redriection	*tmp;

	red = new_red(type, file);
	if (!cmd->red)
		cmd->red = red;
	else
	{
		tmp = cmd->red;
		while (tmp->next && tmp->file_or_delim != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = red;
	}
}
