/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:48:04 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/12 16:12:44 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "./Includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	sizesrc;
	size_t	sizedst;

	if (dst == NULL || src == NULL)
		return (0);
	i = 0;
	j = 0;
	sizesrc = ft_strlen(src);
	while (dst[i] != '\0' && i < size)
		i++;
	sizedst = i;
	if (size == 0 || size <= sizedst)
		return (sizesrc + size);
	while (src[j] != '\0' && size - sizedst - 1 > j)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (sizedst + sizesrc);
}
