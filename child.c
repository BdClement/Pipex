/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:32:07 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/05 14:27:58 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Pour lire, le child2 a besoin que le parent ferme ses pipesFD
// Fonction intermediaire a mon main qui cree le pipe
// et fork 2 fois pour les deux processus fils
// close les bouts de pipe et free les paths
// Puis attends les processus fils pour terminer
void	pipex_fork(t_pipex *pipex, char **envp, char **argv)
{
	int	status;

	pipex->all_paths = find_cmd_paths(envp);
	if (pipe(pipex->pipe) < 0)
		perror("Error");
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		perror("Error");
	else if (pipex->pid1 == 0)
		child1(*pipex, envp, argv);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		perror("Error");
	else if (pipex->pid2 == 0)
		child2(*pipex, envp, argv);
	free_double_char(pipex->all_paths);
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
	waitpid(pipex->pid1, &status, 0);
	waitpid(pipex->pid2, &status, 0);
}

// Le processus fils se charge d'executer la cmd1 et de diriger le resultat
// de cette execution dans le bout d'ecriture du pipe que l'on a cree
void	child1(t_pipex pipex, char **envp, char **argv)
{
	if (pipex.infile == -1)
		child1_error_case(pipex, argv, 1);
	pipex.cmd_args = ft_split(argv[2], ' ');
	dup2(pipex.infile, STDIN_FILENO);
	dup2(pipex.pipe[1], STDOUT_FILENO);
	close(pipex.pipe[0]);
	if (ft_strchr(argv[2], '/') != NULL)
	{
		if (execve(argv[2], pipex.cmd_args, envp) == -1)
			child1_error_case(pipex, argv, 2);
	}
	else
	{
		pipex.cmd_path = find_full_path(pipex);
		if (pipex.cmd_path != NULL)
		{
			if (execve(pipex.cmd_path, pipex.cmd_args, envp) == -1)
				child1_error_case(pipex, argv, 3);
		}
		else
			child1_error_case(pipex, argv, 4);
	}
	exit(EXIT_SUCCESS);
}

// Gestion des cas d'erreurs pour le processus1. Les differents cas sont :
// 1 Le open du infile a renvoye -1
// 2 L'excecution de la commande donne avec le Path n'a pas fonctionne
// 3 La commande donne existe mais son execution a echouee
// 4 La commande n'existe pas
void	child1_error_case(t_pipex pipex, char **argv, int cas)
{
	if (pipex.outfile != -1)
		close(pipex.outfile);
	close(pipex.pipe[1]);
	free_double_char(pipex.all_paths);
	if (cas == 1)
		close(pipex.pipe[0]);
	else if (cas == 2)
		perror(argv[2]);
	else if (cas == 3)
		perror(argv[2]);
	else if (cas == 4)
	{
		ft_putstr_fd(pipex.cmd_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (cas != 1)
	{
		close(pipex.infile);
		free_double_char(pipex.cmd_args);
	}
	exit(EXIT_FAILURE);
}

// Le processus parent recupere lui a parir du bout de lecture du pipe le
// resultat de la cmd1 et l'utilise comme entree standard pour l'execution
// de la cmd2. Il dirige le resultat de la cmd2 dans le file2
void	child2(t_pipex pipex, char **envp, char **argv)
{
	if (pipex.outfile == -1)
		child2_error_case(pipex, argv, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	dup2(pipex.pipe[0], STDIN_FILENO);
	dup2(pipex.outfile, STDOUT_FILENO);
	close(pipex.pipe[1]);
	if (ft_strchr(argv[3], '/') != NULL)
	{
		if (execve(argv[3], pipex.cmd_args, envp) == -1)
			child2_error_case(pipex, argv, 2);
	}
	else
	{
		pipex.cmd_path = find_full_path(pipex);
		if (pipex.cmd_path != NULL)
		{
			if (execve(pipex.cmd_path, pipex.cmd_args, envp) == -1)
				child2_error_case(pipex, argv, 3);
		}
		else
			child2_error_case(pipex, argv, 4);
	}
	exit(EXIT_SUCCESS);
}

// Gestion des cas d'erreurs pour le processus2. Les differents cas sont :
// 1 Le open du outfile a renvoye -1
// 2 L'excecution de la commande donne avec le Path n'a pas fonctionne
// 3 La commande donne existe mais son execution a echouee
// 4 La commande n'existe pas
void	child2_error_case(t_pipex pipex, char **argv, int cas)
{
	if (pipex.infile != -1)
		close(pipex.infile);
	close(pipex.pipe[0]);
	free_double_char(pipex.all_paths);
	close(pipex.outfile);
	if (cas == 1)
		close(pipex.pipe[1]);
	else if (cas == 2)
		perror(argv[3]);
	else if (cas == 3)
		perror(argv[3]);
	else if (cas == 4)
	{
		ft_putstr_fd(pipex.cmd_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (cas != 1)
	{
		close(pipex.outfile);
		free_double_char(pipex.cmd_args);
	}
	exit(EXIT_FAILURE);
}
