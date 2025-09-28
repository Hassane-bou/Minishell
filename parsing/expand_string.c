/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:08:25 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/28 15:12:55 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_exit_status(char *res, int g_exit_status)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(g_exit_status);
	tmp = ft_strjoin(res, str);
	free(res);
	free(str);
	return (tmp);
}

char	*expand_var_value(char *word, t_expand *ex)
{
	int		start;
	char	*value;
	char	*var_name;
	char	*tmp;
	char	*tmp2;

	start = 0;
	start = ex->i;
	tmp2 = NULL;
	tmp = NULL;
	while (word[ex->i] && is_valid_env_char(word[ex->i]))
		(ex->i)++;
	var_name = ft_substr(word, start, ex->i - start);
	if (!var_name)
		return (ex->res);
	value = get_env_value_par(var_name, ex->envp);
	if (value && ex->quote != '\'')
	{
		tmp = ft_strjoin(ex->res, value);
		free(ex->res);
		ex->res = tmp;
	}
	else if (ex->quote == '\'')
		expand_helper(tmp, tmp2, ex, var_name);
	return (free(var_name), ex->res);
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

int	handle_dollar(char *word, t_expand *ex, t_env *env_head)
{
	ex->f = 1;
	ex->i++;
	if (word[ex->i] == '?' && ex->quote != '\'')
	{
		ex->res = expand_exit_status(ex->res, env_head->exit_status);
		if (!ex->res)
			return (0);
		ex->i++;
	}
	else
	{
		ex->res = expand_var_value(word, ex);
		if (!ex->res)
			return (0);
	}
	return (1);
}

char	*expand_string(char *word, t_expand *ex, t_env *env_head)
{
	initialiser_vars(ex);
	if (!word || !ex->res)
		return (ft_strdup(""));
	while (word[ex->i])
	{
		if (check_expand_quotes(word[ex->i], &ex->quote))
			ex->i++;
		else if (word[ex->i] == '$')
		{
			if (!handle_dollar(word, ex, env_head))
				return (ft_strdup(""));
		}
		else
			ex->res = append_char(ex->res, word[ex->i++]);
		if (!ex->res)
			return (ft_strdup(""));
	}
	return (ex->res);
}
