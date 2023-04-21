/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:06:28 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/21 19:07:33 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/get_next_line.h"

/**
 * @brief Stocker le contenu qui a ete lu dans la liste
 * @param lst La liste a remplir
 * @param buf Ce qui a ete lu et stocker dans buf
 * @param nb_read Le nombre de caractere lu
 */
void	stock_in_list(t_lst **lst, char *buf, int nb_read)
{
	t_lst	*new_elem;
	t_lst	*tmp;
	int		i;

	i = 0;
	new_elem = malloc(sizeof(t_lst));
	if (new_elem == NULL)
		return ;
	new_elem->content = malloc(nb_read + 1);
	if (new_elem->content == NULL)
		return ;
	new_elem->next = NULL;
	while (buf[i] != '\0')
	{
		new_elem->content[i] = buf[i];
		i++;
	}
	new_elem->content[i] = '\0';
	if (*lst != NULL)
	{
		tmp = ft_lst_last(*lst);
		tmp->next = new_elem;
	}
	else
		*lst = new_elem;
}

/**
 * @brief Lis jusqu'a trouver un '\n', et ajoute a la liste tout ce qui
 *  a ete lu grace a la fonction stock_in_list
 * @param fd
 * @param lst
 */
void	read_and_stock(int fd, t_lst **lst)
{
	char	*buf;
	int		nb_read;

	nb_read = 1;
	buf = NULL;
	while (contain_new_line(*lst) == 0 && nb_read != 0)
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1 || (*lst == NULL && nb_read == 0))
		{
			free(buf);
			buf = NULL;
			return ;
		}
		buf[nb_read] = '\0';
		stock_in_list(lst, buf, nb_read);
		free(buf);
	}
}

/**
 * @brief Recuperer le contenu stocke dans la liste
 * jusqu'au premier saut de ligne
 * @param lst
 * @param str
 */
void	get_line(t_lst *lst, char	**str)
{
	int	i;
	int	j;

	j = 0;
	create_line(lst, str);
	if (*str == NULL)
		return ;
	while (lst != NULL)
	{
		i = 0;
		while (lst->content[i] != '\0' && lst->content[i] != '\n')
			(*str)[j++] = lst->content[i++];
		if (lst->content[i] == '\n')
		{
			(*str)[j++] = lst->content[i++];
			break ;
		}
		lst = lst->next;
	}
	(*str)[j] = '\0';
}

/**
 * @brief Recuperer ce qui n'a pas ete renvoyer par get_next_line
 *  mais qui a ete lu
 * @param lst
 */
void	clean_lst(t_lst **lst)
{
	int		i;
	int		k;
	t_lst	*tmp;
	t_lst	*rest_of_line;

	i = 0;
	k = 0;
	rest_of_line = malloc(sizeof(t_lst));
	if (rest_of_line == NULL || *lst == NULL)
		return ;
	rest_of_line->next = NULL;
	tmp = ft_lst_last(*lst);
	while (tmp->content[i] != '\n' && tmp->content[i] != '\0')
		i++;
	if (tmp->content != NULL && tmp->content[i] == '\n')
		i++;
	rest_of_line->content = malloc(ft_strlen(tmp->content) - i + 1);
	if (rest_of_line->content == NULL)
		return ;
	while (tmp->content[i] != '\0')
		rest_of_line->content[k++] = tmp->content[i++];
	rest_of_line->content[k] = '\0';
	free_lst(lst);
	*lst = rest_of_line;
}

// Ajout du parametre free_still_recheable pour retirer les still_reachable
// lorsqu'on le lit pas jusquen fin de fichier
// comme dans mon here_doc de Pipex
char	*get_next_line(int fd, int free_still_reachable)
{
	char			*line;
	static t_lst	*lst = NULL;

	line = NULL;
	if (free_still_reachable == 1)
	{
		free_lst(&lst);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_stock(fd, &lst);
	if (lst == NULL)
		return (NULL);
	get_line(lst, &line);
	clean_lst(&lst);
	if (line[0] == '\0')
	{
		free_lst(&lst);
		lst = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
