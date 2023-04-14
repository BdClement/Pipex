/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:44:09 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/12 16:12:21 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include "./Includes/libft.h"

static size_t	ft_count_str(char const *str, char c)
{
	size_t	i;
	size_t	nb;

	if (str == NULL)
		return (0);
	i = 0;
	nb = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			nb++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (nb);
}

static char	*ft_dup(char const *src, int j)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	new = malloc(sizeof(char) * (j + 1));
	if (new == NULL)
		return (NULL);
	while (i < j && src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static void	*freesplit(char **tab, int size)
{
	while (size--)
		free(tab[size]);
	return (NULL);
}

static size_t	ft_charlen(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	j;
	size_t	size;

	if (s == NULL)
		return (NULL);
	i = 0;
	size = ft_count_str(s, c);
	tab = malloc(sizeof(char *) * (size + 1));
	if (tab == NULL)
		return (NULL);
	while (i < size)
	{
		while (*s == c)
			s++;
		j = ft_charlen(s, c);
		tab[i] = ft_dup(s, j);
		if (tab[i] == NULL)
			return (freesplit(tab, i));
		s = s + j;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
