/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:08:51 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/12 16:09:30 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/libft.h"

int	ft_atoi(const char *nptr)
{
	long int	value;
	int			sign;

	value = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		value = value * 10 + (*nptr - 48);
		nptr++;
	}
	return ((int)value * sign);
}
