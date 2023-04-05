/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:15:49 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/05 14:25:23 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Rappel
// valgrind --leak-check=full --track-fds=yes --trace-children=yes
//./pipex /dev/stdin "cat" "ls" /dev/stdout Blocage a cause des close FD
// 3 fd a fermer processus daron
// FONCTION find_cmd_paths
// Retrouve la ligne qui contient l'ensemble des path dans envp
// Retire le debut ("PATH=")
// Et retourne le split du reste de la ligne avec donc l'ensemble des path
char	**find_cmd_paths(char **envp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
		{
			while (envp[i][j] != '=')
				j++;
			return (ft_split(envp[i] + j + 1, ':'));
		}
		i++;
	}
	return (NULL);
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

//Trouve grace a access() le bon path a envoyer a execve
char	*find_full_path(t_pipex pipex)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (pipex.all_paths != NULL)
	{
		while (pipex.all_paths[i])
		{
			cmd_path = ft_join(pipex.all_paths[i++], pipex.cmd_args[0]);
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
			free(cmd_path);
		}
	}
	return (NULL);
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

// O_TRUNC Permet d'ecraser le resultat si file2 n'est pas vide
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		ft_putstr_fd("Nombre d'arguments incorrect\n", 2);
		return (1);
	}
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == -1)
		perror(argv[1]);
	pipex.outfile = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0744);
	if (pipex.outfile == -1)
		perror(argv[4]);
	pipex_fork(&pipex, envp, argv);
	close(pipex.infile);
	close(pipex.outfile);
	if (pipex.infile == -1 || pipex.outfile == -1)
		return (1);
	return (0);
}
