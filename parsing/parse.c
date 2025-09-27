/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:50:48 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/24 12:00:19 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*add_back_cmd(t_cmd **cmd, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!cmd || !new_cmd)
		return (NULL);
	if (!*cmd)
		*cmd = new_cmd;
	else
	{
		tmp = *cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
	return (new_cmd);
}

void	cmd_add(t_token *token, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
		{
			cmd->args[i] = ft_strdup(token->value);
			if (!cmd->cmd)
				cmd->cmd = ft_strdup(token->value);
			i++;
		}
		else if (token->type == REDIR_OUT || token->type == APPEND
			|| token->type == REDIR_IN || token->type == HEREDOC)
		{
			if (token->next)
				add_red(token->type, cmd, token->next->value);
			token = token->next;
		}
		token = token->next;
	}
	cmd->args[i] = NULL;
	cmd->next = NULL;
}

t_cmd	*new_cmd(t_token *token)
{
	t_cmd	*cmd;
	int		nbr_args;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	initilisation(cmd);
	nbr_args = count_word_in_token(token);
	cmd->args = malloc(sizeof(char *) * (nbr_args + 2));
	if (!cmd->args)
		return (free(cmd), NULL);
	cmd_add(token, cmd);
	if (token->quoted == 1)
		cmd->quoted_del = 1;
	return (cmd);
}

t_cmd	*parse_cmd(t_token *token)
{
	t_cmd	*head;
	t_cmd	*cmd;

	head = NULL;
	while (token)
	{
		cmd = new_cmd(token);
		add_back_cmd(&head, cmd);
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->type == PIPE)
			token = token->next;
	}
	return (head);
}
