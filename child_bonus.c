/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:38:43 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/14 20:41:15 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	malloc_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->pipe = malloc(sizeof(*pipex->pipe) * pipex->nb_pipe);
	//Check malloc OK
	while (i < pipex->nb_pipe)
	{
		pipex->pipe[i] = malloc(sizeof(int) * 2);
		//Check malloc OK
		// if (pipe(pipex->pipe[i]) < 0) // Faire tout les pipe dans ma fonction malloc_pipes ??
		// 	perror("Error");
		i++;
	}
}

// void	close_pipes(t_pipex pipex, int index)
// {
// 	int	i;

// 	i = index;
// 	if (i >= 1)
// 	{
// 		while (index < pipex.nb_pipe - 1)
// 		{
// 			close(pipex.pipe[index][0]);
// 			close(pipex.pipe[index][1]);
// 			index++;
// 		}
// 		while (i > 0)
// 		{
// 			close(pipex.pipe[i - 1][0]);
// 			close(pipex.pipe[i - 1][1]);
// 			i--;
// 		}
// 	}
// }


// Le processus fils se charge d'executer la cmd1 et de diriger le resultat
// de cette execution dans le bout d'ecriture du pipe que l'on a cree
void	child_process(t_pipex *pipex, char **envp, char **argv, int index)
{
	// if (pipex.infile == -1)
	// 	child1_error_case(pipex, argv, 1);
	if (index != 0)
		free_double_char(pipex->cmd_args);
	pipex->cmd_args = ft_split(argv[index + pipex->cmd_start], ' ');
	// Creation d'une fonction de redirection ??
	if (index == 0 && envp)
	{
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipex->pipe[index][1], STDOUT_FILENO);
		close(pipex->pipe[index][0]);
	}
	else if (index == pipex->nb_cmd -1)
	{
		dup2(pipex->pipe[index - 1][0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->pipe[index - 1][1]);
	}
	else
	{
		dup2(pipex->pipe[index - 1][0], STDIN_FILENO);
		dup2(pipex->pipe[index][1], STDOUT_FILENO);
		close(pipex->pipe[index - 1][1]);
		close(pipex->pipe[index][0]);
	}
	if (ft_strchr(argv[pipex->cmd_start + index], '/') != NULL)
	{
		if (execve(argv[pipex->cmd_start + index], pipex->cmd_args, envp) == -1)
			printf("Marche pas 1");
			// child1_error_case(pipex, argv, 2);
	}
	else
	{
		printf("JE rentre dans le else exec %d\n", index);
		// pipex->cmd_path = find_full_path(*pipex);
		if (pipex->cmd_path != NULL)
		{
			if (execve(pipex->cmd_path, pipex->cmd_args, envp) == -1)
				printf("Marche pas 2");
				// child1_error_case(pipex, argv, 3);
		}
		else
			printf("Command not found");
			// child1_error_case(pipex, argv, 4);
	}
	if (index == 0)
		close(pipex->pipe[index][1]);
	else if (index == pipex->nb_cmd -1)
		close(pipex->pipe[index - 1][0]);
	else
	{
		close(pipex->pipe[index - 1][0]);
		close(pipex->pipe[index][1]);
	}
	exit(EXIT_SUCCESS);
}

// Faire un pipe puis un fork
void	pipex_fork_bonus(t_pipex *pipex, char **envp, char **argv)
{
	int	i;
	int	status;

	i = 0;
	if (argv && envp)
		printf("");
	pipex->all_paths = find_cmd_paths(envp);
	malloc_pipes(pipex);
	while (i < pipex->nb_cmd)
	{
		if (i < pipex->nb_pipe)
		{
			if (pipe(pipex->pipe[i]) < 0) // Faire tout les pipe dans ma fonction malloc_pipes ??
			perror("Error");
		}
		pipex->pid = fork();
		if (pipex->pid < 0)
			perror("Error");
		else if (pipex->pid == 0)
			child_process(pipex, envp, argv, i);
		waitpid(-1, &status, 0);
		if (i >= 1)
		{
			close(pipex->pipe[i - 1][0]);
			close(pipex->pipe[i - 1][1]);
		}
		i++;
	}
	// Boucle de wait tout les fils
}

// Remplie le fichier temporaire here_doc cree
void	fill_here_doc(t_pipex pipex)
{
	char	*str;

	str = NULL;
	while (1)
	{
		ft_putstr_fd("> ", 0);
		str = get_next_line(0);
		if (ft_strlen(str) == ft_strlen(pipex.LIMITER) + 1
			&& ft_strncmp(str, pipex.LIMITER, ft_strlen(pipex.LIMITER)) == 0)
			break ;
		ft_putstr_fd(str, pipex.infile);
	}
}

// Faire une boucle de get_next_line de 0
// Ecrire la line recuperer dans mon fichier temporaire here_doc
// Sans le O_TRUNC pour pouvoir ecrire a la suite
void	init_struct(t_pipex *pipex, int argc, char **argv)
{
	if (argv[1] != NULL && ft_strncmp(argv[1], "here_doc", 8) == 0
		&& ft_strlen(argv[1]) == ft_strlen("here_doc"))
	{
		pipex->here_doc = 1;
		pipex->nb_cmd = argc - 4;
		pipex->cmd_start = 3;
		pipex->infile = open("/tmp/here_doc_tmp", O_CREAT | O_RDWR, 0777); // A supprimer avec unlink en fin de programme
		pipex->LIMITER = argv[2];

		pipex->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY, 0744);
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
	if (pipex->infile == -1)
		perror(argv[1]);
	if (pipex->outfile == -1)
		perror(argv[4]);
}
