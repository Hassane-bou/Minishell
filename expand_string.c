/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:08:25 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/22 10:36:06 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialiser_vars(t_expand *e)
{
	e->res = ft_strdup("");
	e->i = 0;
	e->g_exit_status = 0;
	e->quote = 0;
	e->f = 0;
}

char	*expand_exit_status(char *res, int g_exit_status)
{
	char	*str;
	char	*tmp;

	g_exit_status = 0;
	str = ft_itoa(g_exit_status);
	tmp = ft_strjoin(res, str);
	free(res);
	free(str);
	return (tmp);
}

char	*expand_var_value(char *word, int *i, char *res, char **envp)
{
	int		start;
	char	*value;
	char	*var_name;
	char	*tmp;

	start = 0;
	start = *i;
	while (word[*i] && is_valid_env_char(word[*i]))
		(*i)++;
	var_name = ft_substr(word, start, *i - start);
	if (!var_name)
		return (res);
	value = get_env_value(var_name, envp);
	if (value)
	{
		tmp = ft_strjoin(res, value);
		free(res);
		res = tmp;
	}
	free(var_name);
	return (res);
}

char	*append_char(char *res, char c)
{
	char	*tmp;

	if (!res)
		return (NULL);
	tmp = ft_strjoin_char(res, c);
	if (tmp)
	{
		free(res);
		res = tmp;
	}
	return (res);
}
int handle_dollar(char *word ,t_expand *ex)
{
	ex->f = 1;
	ex->i++;
	if (word[ex->i] == '?')
	{
		ex->res = expand_exit_status(ex->res, ex->g_exit_status);
		if (!ex->res)
			return (0);
		ex->i++;
	}
	else
	{
		ex->res = expand_var_value(word, &ex->i, ex->res, ex->envp);
		if (!ex->res)
			return (0);
	}
	return(1);
}


char	*expand_string(char *word, t_expand *ex)
{
	initialiser_vars(ex);
	if (!word || !ex->res)
		return (ft_strdup(""));
	while (word[ex->i])
	{
		if (check_expand_quotes(word[ex->i], &ex->quote))
			ex->i++;
		else if (word[ex->i] == '$' && ex->quote != '\'')
		{
			if(!handle_dollar(word,ex))
				return(ft_strdup(""));
		}
		else
			ex->res = append_char(ex->res, word[ex->i++]);
		if (!ex->res)
			return (ft_strdup(""));
	}
	return (ex->res);
}
