/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:58:54 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/27 12:18:52 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_quotes(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (0);
		i++;
	}
	return (1);
}

int	check_expand_quotes(char c, char *quote)
{
	if (c == '\'' && *quote == 0)
		return (*quote = '\'', 1);
	else if (c == '\'' && *quote == '\'')
		return (*quote = 0, 1);
	else if (c == '"' && *quote == 0)
		return (*quote = '"', 1);
	else if (c == '"' && *quote == '"')
		return (*quote = 0, 1);
	return (0);
}

void	free_split(char **value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		free(value[i]);
		i++;
	}
	free(value);
}

void	expand_loop_list(t_token **head, t_expand *exp, t_env *env_head)
{
	t_token	*prev;

	exp->tmp = *head;
	prev = NULL;
	while (exp->tmp)
	{
		exp->f = 0;
		if (exp->tmp->type == HEREDOC && exp->tmp->next)
			exp->tmp = expand_heredoc(exp->tmp);
		else if ((exp->tmp->type == REDIR_IN || exp->tmp->type == REDIR_OUT
				|| exp->tmp->type == APPEND) && exp->tmp->next)
			exp->tmp = expand_redirection(exp->tmp, exp, env_head);
		else if (exp->tmp->type == WORD && exp->tmp->value)
			exp->tmp = expand_word(exp, head, &prev, env_head);
		else
		{
			prev = exp->tmp;
			exp->tmp = exp->tmp->next;
		}
	}
}

void	expand_token_list(t_token **head, char **envp, t_env *env_head)
{
	t_expand	exp_struct;
	t_expand	*exp;

	if (!head || !*head)
		return ;
	exp = &exp_struct;
	exp->envp = envp; 
	expand_loop_list(head, exp, env_head);
}
