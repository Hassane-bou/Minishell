/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:39:46 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/24 12:11:30 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_herdoc(char *input, int i, t_token **head)
{
	char	*word;
	t_token	*new;

	word = ft_substr(input, i, 2);
	new = create_token(word, HEREDOC);
	append_token(head, new);
	free(word);
	i += 2;
	return (i);
}

int	handle_append(char *input, int i, t_token **head)
{
	t_token	*new_token;
	char	*word;

	word = ft_substr(input, i, 2);
	new_token = create_token(word, APPEND);
	append_token(head, new_token);
	free(word);
	i += 2;
	return (i);
}

int	handle_outfile(char *input, int i, t_token **head)
{
	char	*word;
	t_token	*new;

	word = ft_substr(input, i, 1);
	new = create_token(word, REDIR_OUT);
	append_token(head, new);
	free(word);
	i++;
	return (i);
}

int	handle_intfile(char *input, int i, t_token **head)
{
	char	*word;
	t_token	*new;

	word = ft_substr(input, i, 1);
	new = create_token(word, REDIR_IN);
	append_token(head, new);
	free(word);
	i++;
	return (i);
}

int	handle_pipe(char *input, int i, t_token **head)
{
	char	*word;
	t_token	*new;

	word = ft_substr(input, i, 1);
	new = create_token(word, PIPE);
	append_token(head, new);
	free(word);
	i++;
	return (i);
}
