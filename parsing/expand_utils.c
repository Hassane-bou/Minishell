/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:58:36 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/27 12:18:58 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*expand_heredoc(t_token *tmp)
{
	char	*old;

	if (!tmp || !tmp->next)
		return (NULL);
	if (!has_quotes(tmp->next->value))
		tmp->quoted = 1;
	old = tmp->next->value;
	tmp->next->value = remove_quotes(tmp->next->value);
	free(old);
	tmp = tmp->next->next;
	return (tmp);
}

t_token	*expand_redirection(t_token *tmp, t_expand *e, t_env *env_head)
{
	char	*expanded;

	if (!tmp || !tmp->next)
		return (NULL);
	if (tmp->next->value && tmp->next->new_quote != '\'')
	{
		expanded = expand_string(tmp->next->value, e, env_head);
		if (expanded)
		{
			free(tmp->next->value);
			tmp->next->value = expanded;
			if (expanded[0] == '\0' && e->f == 1)
				return (tmp->next->next);
		}
	}
	return (tmp->next->next);
}

t_token	*expand_word(t_expand *e, t_token **head, t_token **prev,
		t_env *env_head)
{
	char	*expand;
	char	**words;

	expand = expand_string(e->tmp->value, e, env_head);
	if (!expand)
		return (e->tmp->next);
	free(e->tmp->value);
	if (ft_strchr(expand, ' ') && e->tmp->new_quote != '"')
	{
		words = ft_split(expand, ' ');
		free(expand);
		if (!words || !words[0])
			return (e->tmp->next);
		e->tmp->value = ft_strdup(words[0]);
		split_tokens(e, words);
		free_splited_token(words);
	}
	else
		e->tmp->value = expand;
	if (e->tmp->value[0] == '\0' && e->f == 1)
		return (remove_empty_token(e, head, prev));
	*prev = e->tmp;
	return (e->tmp->next);
}
