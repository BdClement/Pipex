/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:43:08 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/27 17:41:42 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Affiche les differents messages d'erreur en foncton du cas
void	error_messages(t_pipex pipex, char **argv, int cas, int index)
{
	char	*str;

	if (cas == 1 && pipex.outfile == -1
		&& (access(argv[pipex.cmd_start - 1], F_OK) == -1))
	{
		str = ft_strjoin(argv[pipex.cmd_start - 1],
				": No such file or directory\n");
		write(2, str, ft_strlen(str));
		free(str);
	}
	else if (cas == 1)
		perror(argv[pipex.cmd_start + index - 1]);
	else if (cas == 2)
		perror(argv[pipex.cmd_start + index + 1]);
	else if (cas == 5 || cas == 3)
	{
		str = ft_strjoin(pipex.cmd_args[0], ": command not found\n");
		write(2, str, ft_strlen(str));
		free(str);
	}
	else
		perror(argv[pipex.cmd_start + index]);
}

// Free un char **
void	free_double_char(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}

// Free un **int
void	free_double_int(int **tab, int tab_size)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (i < tab_size)
			free(tab[i++]);
		free(tab);
	}
}

// Alloue la memoire suffisante au tableau de int[2]
void	malloc_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->pipe = malloc(sizeof(*pipex->pipe) * pipex->nb_pipe);
	if (pipex->pipe == NULL)
		return ;
	while (i < pipex->nb_pipe)
	{
		pipex->pipe[i] = malloc(sizeof(int) * 2);
		if (pipex->pipe[i] == NULL)
			return ;
		i++;
	}
}

//Similaire a un ft_strjoin en ajoutant la commande a la fin du path
// A la seule difference qu'on rajoute ici '/' pour completer le path
// Et ensuite ajouter le fichier qui comprend la commande du meme nom
char	*ft_join(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (str == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	while (i < ft_strlen(s1) + ft_strlen(s2) + 1)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
