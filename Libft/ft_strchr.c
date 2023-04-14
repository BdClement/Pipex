/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:25:15 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/12 16:12:26 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "./Includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = (char *) s;
	while (*str != '\0')
	{
		if ((unsigned char)*str == (unsigned char)c)
			return (str);
		str++;
	}
	if (c == 0)
		return ((char *)str);
	return (NULL);
}
