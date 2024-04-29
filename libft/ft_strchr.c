/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maglagal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:43:45 by maglagal          #+#    #+#             */
/*   Updated: 2023/11/10 13:52:34 by maglagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;
	char			*p;

	i = 0;
	cc = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == cc)
		{
			p = (char *)s + i;
			while (s[i])
				i++;
			return (p);
		}
		else
			i++;
	}
	if (cc == '\0')
		return ((char *)s + i);
	return (0);
}
