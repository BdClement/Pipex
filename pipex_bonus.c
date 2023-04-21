/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:31:36 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/21 14:04:10 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Rappel
// valgrind --leak-check=full --track-fds=yes --trace-children=yes

// Cette fonction stocke dans la structure l'ensemble des informations
// dont le programme aura besoin par la suite
// O_APPEND permet d'ouvrir l'outfile en mode ajout en placant la tete de
// lecture/ecriture en fin de ficher
// O_TRUNC Permet d'ecraser le resultat si outfile n'est pas vide
void	init_struct(t_pipex *pipex, int argc, char **argv)
{
	if (argv[1] != NULL && ft_strncmp(argv[1], "here_doc", 8) == 0
		&& ft_strlen(argv[1]) == ft_strlen("here_doc"))
	{
		pipex->here_doc = 1;
		pipex->nb_cmd = argc - 4;
		pipex->cmd_start = 3;
		pipex->limiter = argv[2];
		pipex->outfile = open(argv[argc - 1],
				O_CREAT | O_APPEND | O_WRONLY, 0744);
	}
	else
	{
		pipex->here_doc = 0;
		pipex->nb_cmd = argc - 3;
		pipex->cmd_start = 2;
		pipex->infile = open(argv[1], O_RDONLY);
		pipex->outfile = open(argv[argc - 1],
				O_CREAT | O_TRUNC | O_WRONLY, 0744);
	}
	pipex->nb_pipe = pipex->nb_cmd - 1;
	pipex->cmd_args = NULL;
	malloc_pipes(pipex);
}

// Remplie le fichier temporaire here_doc cree
void	fill_here_doc(t_pipex *pipex)
{
	char	*str;
	int		file;

	file = open("/tmp/here_doc_tmp", O_CREAT | O_RDWR, 0777);
	while (1 && file != -1)
	{
		ft_putstr_fd("> ", 0);
		str = get_next_line(0, 0);
		if (ft_strlen(str) == ft_strlen(pipex->limiter) + 1
			&& ft_strncmp(str, pipex->limiter, ft_strlen(pipex->limiter)) == 0)
		{
			get_next_line(file, 1);
			free(str);
			break ;
		}
		ft_putstr_fd(str, file);
		free(str);
	}
	close(file);
	pipex->infile = open("/tmp/here_doc_tmp", O_RDONLY);
	if (pipex->infile == -1)
	{
		unlink("/tmp/here_doc_tmp");
		perror("Error");
	}
}

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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	init_struct(&pipex, argc, argv);
	if ((pipex.here_doc == 1 && argc < 6) || (pipex.here_doc == 0 && argc < 5))
	{
		ft_putstr_fd("Nombre d'arguments incorrect\n", 2);
		return (1);
	}
	pipex.all_paths = find_cmd_paths(envp);
	if (pipex.here_doc == 1)
		fill_here_doc(&pipex);
	pipex_fork_bonus(&pipex, envp, argv);
	close(pipex.infile);
	close(pipex.outfile);
	if (pipex.here_doc == 1)
		unlink("/tmp/here_doc_tmp");
	if (pipex.infile == -1 || pipex.outfile == -1)
		return (1);
	return (0);
}
