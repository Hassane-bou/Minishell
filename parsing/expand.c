/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:58:54 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/23 10:50:25 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


// t_token	*export_value(char *export)
// {
// 	t_token	*new_token;
// 	t_token	*head;
// 	t_token	*tmp;
// 	char	**value;
// 	int		i;

// 	i = 0;
// 	value = ft_split(export, ' ');
// 	if (!value || !value[0])
// 	{
// 		free_split(value);
// 		return (NULL);
// 	}
// 	tmp = cretae_token(value[i], WORD);
// 	if (!tmp)
// 	{
// 		free_split(value);
// 		return (NULL);
// 	}
// 	head = tmp;
// 	i++;
// 	while (value[i])
// 	{
// 		new_token = cretae_token(value[i], WORD);
// 		if (!new_token)
// 		{
// 			free_split(value);
// 			return (NULL);
// 		}
// 		tmp->next = new_token;
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	free_split(value);
// 	return (head);
// }

void expand_loop_list(t_token **head, t_expand *exp)
{
	t_token	*tmp;
	t_token *prev;

	tmp = *head;
	prev = NULL;
	while (tmp)
	{
		exp->f = 0;
		if (tmp->type == HEREDOC && tmp->next)
		{
			tmp = expand_heredoc(tmp, exp);
			// printf("->->->%d\n", tmp->new_quote);
		}
		else if ((tmp->type == REDIR_IN || tmp->type == REDIR_OUT
				|| tmp->type == APPEND) && tmp->next)
			tmp = expand_redirection(tmp, exp);
		else if (tmp->type == WORD && tmp->value && tmp->new_quote != '\'')
			tmp = expand_word(tmp, exp, head, &prev);
		else
		{
			prev = tmp;
			tmp = tmp->next;
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
	expand_loop_list(head, exp);
}
