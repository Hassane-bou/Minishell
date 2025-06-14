/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haboucha <haboucha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:55:04 by haboucha          #+#    #+#             */
/*   Updated: 2025/06/14 09:53:34 by haboucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strlen(char *s)
{
    int i = 0;
    while(s[i])
        i++;
    return(i);
}

char	*ft_strdup( char *s1)
{
	char	*p;
	int		n;
	int		i;

	p = (char *)s1;
	n = ft_strlen(s1) + 1;
	i = 0;
	p = (char *)malloc(n * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (s1[i])
	{
		p[i] = (char)s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
