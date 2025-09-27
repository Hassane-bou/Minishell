/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:07:58 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/25 13:13:50 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_helper(char *tmp, char *tmp2, t_expand *ex, char *var_name)
{
	tmp = ft_strjoin(ex->res, "$");
	tmp2 = ft_strjoin(tmp, var_name);
	free(tmp);
	free(ex->res);
	ex->res = tmp2;
}

void	free_splited_token(char **word)
{
	int	i;

	i = 0;
	while (word[i++])
		free(word[i]);
	free(word);
}

t_token	*remove_empty_token(t_expand *e, t_token **head, t_token **prev)
{
	t_token	*to_free;

	to_free = e->tmp;
	if (*prev)
		(*prev)->next = e->tmp->next;
	else
		*head = e->tmp->next;
	e->tmp = e->tmp->next;
	free(to_free->value);
	free(to_free);
	return (e->tmp);
}

void	split_tokens(t_expand *e, char **words)
{
	int		i;
	t_token	*curr;
	t_token	*last_new;

	last_new = e->tmp;
	i = 1;
	while (words[i])
	{
		curr = malloc(sizeof(t_token));
		if (!curr)
			break ;
		curr->value = ft_strdup(words[i]);
		curr->type = WORD;
		curr->new_quote = 0;
		curr->quoted = 0;
		curr->next = last_new->next;
		last_new->next = curr;
		last_new = curr;
		i++;
	}
}
