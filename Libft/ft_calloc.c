/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:38:29 by clbernar          #+#    #+#             */
/*   Updated: 2022/11/28 19:03:54 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*calloc;

	calloc = NULL;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((int) size < 0)
		return (NULL);
	calloc = malloc(nmemb * size);
	if (calloc == NULL)
		return (NULL);
	ft_bzero(calloc, nmemb * size);
	return (calloc);
}
