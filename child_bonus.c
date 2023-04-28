/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:38:43 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/27 16:53:14 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Effectue les differentes redirections possibles pour les cas suivants :
//-Le premier processus qui recupere les donnees de l'infile
//-Le dernier processus qui execute sa commande dans l'outfile
//-Les processus intermediaires qui lisent depuis pipe[index - 1][0]
// et ecrivent dans pipe[index][1]
void	redirection(t_pipex *pipex, int index)
{
	if (index == 0)
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
}

// Ferme les bout de pipe ouvert
// Deux cas sont possible :
//-Soit le processus n'a pas rencontre de cas d'erreur ou soit le cas derreur se
// situe apres l'appel a la fonction redirection qui elle ferme les bouts
// inutilises Donc seulement certains bouts sont close
//-Soit le cas d'erreur rencontre se situe avant l'appel a redirection() donc
// Tous les bouts sont close
void	close_pipes(t_pipex *pipex, int index, int error_case)
{
	if (index == 0)
	{
		close(pipex->pipe[index][1]);
		if (error_case == 1)
			close(pipex->pipe[index][0]);
	}
	else if (index == pipex->nb_cmd -1)
	{
		close(pipex->pipe[index - 1][0]);
		if (error_case == 2)
			close(pipex->pipe[index - 1][1]);
	}
	else
	{
		close(pipex->pipe[index - 1][0]);
		close(pipex->pipe[index][1]);
	}
}

// Gere les cas d'erreurs dans l'execution d'un child process
// -Ferme d'abord les fd du infile et de l'outfile
// -Close les bout de pipe qu'il faut fermer en fonction du cas d'erreur
// -Affiche les messages d'erreurs
// -Free ce qu'il faut free en fonction du cas d'erreur
void	child_bonus_error_case(t_pipex pipex, char **argv, int cas, int index)
{
	if (pipex.outfile != -1)
		close(pipex.outfile);
	if (pipex.infile != -1)
		close(pipex.infile);
	close_pipes(&pipex, index, cas);
	error_messages(pipex, argv, cas, index);
	if (cas == 4)
		free(pipex.cmd_path);
	if (cas > 2)
		free_double_char(pipex.cmd_args);
	free_double_char(pipex.all_paths);
	free_double_int(pipex.pipe, pipex.nb_pipe);
	exit(EXIT_FAILURE);
}

// Cette fonction est appele pour chaque fork() effetcue
// L'index permet de definir le comportement que le processus doit avoir
void	child_process(t_pipex *pipex, char **envp, char **argv, int index)
{
	if (pipex->infile == -1 && index == 0)
		child_bonus_error_case(*pipex, argv, 1, index);
	if (pipex->outfile == -1 && index == pipex->nb_cmd - 1)
		child_bonus_error_case(*pipex, argv, 2, index);
	pipex->cmd_args = ft_split(argv[index + pipex->cmd_start], ' ');
	redirection(pipex, index);
	if (ft_strchr(argv[pipex->cmd_start + index], '/') != NULL)
	{
		if (execve(argv[pipex->cmd_start + index], pipex->cmd_args, envp) == -1)
			child_bonus_error_case(*pipex, argv, 3, index);
	}
	else
	{
		pipex->cmd_path = find_full_path(*pipex);
		if (pipex->cmd_path != NULL)
		{
			if (execve(pipex->cmd_path, pipex->cmd_args, envp) == -1)
				child_bonus_error_case(*pipex, argv, 4, index);
		}
		else
			child_bonus_error_case(*pipex, argv, 5, index);
	}
}

// Fait une boulce avec autant de fork que de commande et
// autant de pipe - 1
void	pipex_fork_bonus(t_pipex *pipex, char **envp, char **argv)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd)
	{
		if (i < pipex->nb_pipe)
		{
			if (pipe(pipex->pipe[i]) < 0)
				perror("Error");
		}
		pipex->pid = fork();
		if (pipex->pid < 0)
			perror("Error");
		else if (pipex->pid == 0)
			child_process(pipex, envp, argv, i);
		if (i >= 1)
		{
			close(pipex->pipe[i - 1][0]);
			close(pipex->pipe[i - 1][1]);
		}
		i++;
	}
	while (i++ < pipex->nb_cmd * 2)
		wait(NULL);
}
