/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:58:36 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/22 10:10:13 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

int	is_valid_env_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '_');
}



char	*get_env_value(char *var, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_stncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}



char	*ft_strjoin_char(char *s1, char c)
{
	int		i;
	int		len;
	char	*p;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) + 1;
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	while (s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = c;
	i++;
	p[i] = '\0';
	return (p);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

t_token	*expand_heredoc(t_token *tmp)
{
	if (!tmp || !tmp->next)
		return (NULL);
	if (!has_quotes(tmp->next->value))
		tmp->quoted = 1;
	tmp->next->value = remove_quotes(tmp->next->value);
	tmp = tmp->next->next;
	return (tmp);
}

t_token	*expand_redirection(t_token *tmp, t_expand *e)
{
	char	*expanded;

	if (!tmp || !tmp->next)
		return (NULL);
	if (tmp->next->value && tmp->next->new_quote != '\'')
	{
		expanded = expand_string(tmp->next->value, e);
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

t_token	*expand_word(t_token *tmp, t_expand *e, t_token **head, t_token **prev)
{
	t_token *to_free;
	char *expand;

	expand = expand_string(tmp->value, e);
	if (expand)
	{
		free(tmp->value);
		tmp->value = expand;
		if (tmp->value[0] == '\0' && e->f == 1)
		{
			to_free = tmp;
			if (*prev)
				(*prev)->next = tmp->next;
			else
				*head = tmp->next;
			tmp = tmp->next;
			free(to_free->value);
			free(to_free);
			return (tmp);
		}
	}
	return (tmp->next);
}
