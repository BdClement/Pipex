/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:28:12 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/12 16:11:44 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "./Includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s3;
	unsigned char	*s4;
	size_t			i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	i = 0;
	while (i++ < n)
	{
		if (*s3 == *s4)
		{
			s3++;
			s4++;
		}
		else
			return (*s3 - *s4);
	}
	return (0);
}
