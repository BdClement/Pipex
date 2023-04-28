/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:49:31 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/21 18:49:39 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# if (BUFFER_SIZE < 0)
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
}					t_lst;

char	*get_next_line(int fd, int free_still_reachable);
int		contain_new_line(t_lst *lst);
t_lst	*ft_lst_last(t_lst *lst);
void	stock_in_list(t_lst **lst, char *buf, int nb_read);
void	read_and_stock(int fd, t_lst **lst);
void	create_line(t_lst *lst, char **str);
void	get_line(t_lst *lst, char	**str);
// size_t	ft_strlen(const char *s);
void	clean_lst(t_lst **lst);
void	free_lst(t_lst **lst);

#endif
