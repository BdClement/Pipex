/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:34:58 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/12 16:12:57 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "./Includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*mapi;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	mapi = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (mapi == NULL)
		return (NULL);
	mapi[ft_strlen(s)] = '\0';
	while (s[i] != '\0')
	{
		mapi[i] = (*f)(i, s[i]);
		i++;
	}
	return (mapi);
}
