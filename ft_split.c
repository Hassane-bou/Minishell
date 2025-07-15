/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:12:04 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/11 15:12:52 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

char	*ft_strncpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*allocate_word(char **pr, int i, int j, int k)
{
	pr[k] = (char *)malloc(sizeof(char *) * (i - j + 1));
	if (!pr[k])
	{
		while (k > 0)
			free(pr[k--]);
		free(pr);
		return (NULL);
	}
	return (pr[k]);
}

// char	**ft_split(char *str, char c)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	**pr;

// 	i = ((j = (k = 0), 0), 0);
// 	pr = (char **)malloc(sizeof(char *) * (ft_count(str, c) + 1));
// 	if (!pr)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		while (str[i] && str[i] == c)
// 			i++;
// 		j = i;
// 		while (str[i] && str[i] != c)
// 			i++;
// 		if (i > j)
// 		{
// 			allocate_word(pr, i, j, k);
// 			ft_strncpy(pr[k++], &str[j], i - j);
// 			j++;
// 		}
// 	}
// 	return (pr[k] = NULL, pr);
// }
