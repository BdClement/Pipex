/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 19:51:16 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/12 16:12:36 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "./Includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (f == NULL)
		return ;
	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			(*f)(i, s + i);
			i++;
		}
	}
}
