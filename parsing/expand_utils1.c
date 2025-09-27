/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:48:17 by haboucha          #+#    #+#             */
/*   Updated: 2025/09/24 13:08:38 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialiser_vars(t_expand *e)
{
	e->res = ft_strdup("");
	e->i = 0;
	e->g_exit_status = 0;
	e->quote = 0;
	e->f = 0;
}

int	is_valid_env_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '_');
}

char	*get_env_value_par(char *var, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
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

	if (!str)
		return (NULL);
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
