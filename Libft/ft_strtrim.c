/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:53:16 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/12 16:13:21 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "./Includes/libft.h"

static size_t	ischar(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	i;
	size_t	j;
	size_t	size;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	j = 0;
	size = ft_strlen(s1) - 1;
	while (ischar(s1[i], set) == 1)
		i++;
	while (ischar(s1[size--], set) == 1)
		j++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	size = ft_strlen(s1) - (i + j - 1);
	trim = malloc(sizeof(char) * (unsigned int)size);
	if (trim == NULL)
		return (NULL);
	j = 0;
	while (j < size - 1)
		trim[j++] = s1[i++];
	trim[j] = '\0';
	return (trim);
}
