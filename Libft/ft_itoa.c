/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:02:23 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/12 16:10:41 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "./Includes/libft.h"

static size_t	ft_size(int n)
{
	size_t	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n != 0)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

static char	*ft_fill(char *str, size_t nb, size_t size)
{
	while (nb > 0)
	{
		str[size--] = 48 + (nb % 10);
		nb = nb / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	nb;
	int		sign;
	size_t	size;

	sign = 1;
	str = NULL;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = ft_size(n);
	str = malloc(sizeof(char) * size + 1);
	if (str == NULL)
		return (NULL);
	str[size--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		sign = -1;
	}
	nb = n * sign;
	str = ft_fill(str, nb, size);
	return (str);
}
