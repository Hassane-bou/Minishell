/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:06:48 by rmouafik          #+#    #+#             */
/*   Updated: 2025/06/11 09:56:11 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	b;

	b = (char)c;
	while (*s)
	{
		if (*s == b)
		{
			return ((char *)s + 1);
		}
		s++;
	}
	if (b == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}
