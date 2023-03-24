/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:15:49 by clbernar          #+#    #+#             */
/*   Updated: 2023/03/22 19:18:51 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"

// Retrouve la ligne qui contient l'ensemble des path dans envp
// Retire le debut ("PATH=")
// Et retourne le split du reste de la ligne avec donc l'ensemble des path
char	**find_cmd_paths(char **envp)
{
	int		i;
	int		j;
	char	**paths;

	paths = NULL;
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
	// Split a Free en fin de programme !!
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

// Le processus fils se charge d'executer la cmd1 et de diriger le resultat
// de cette execution dans le bout d'ecriture du pipe que l'on a cree
void	child_part(int file1, int *fd, char **envp, char **argv)
{
	char	**cmd_arg;
	char	**paths;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_arg = ft_split(argv[2], ' ');
	paths = find_cmd_paths(envp);
	//REDIRECTION
	dup2(file1, STDIN_FILENO);// La nouvelle entree standard est file1
	dup2(fd[1], STDOUT_FILENO); // La nouvelle sortie standard est le bout d'ecriture du pipe
	close(fd[0]);// fermer le bout de lecture que l'on utilise pas;
	//TEST EXECUTION AVEC EXECVE Avec chaque PATH
	while (paths[i])
	{
		cmd_path = ft_join(paths[i], cmd_arg[0]);
		execve(cmd_path, cmd_arg, envp);
		free(cmd_path);
		i++;
	}
	close(fd[1]);
}

// Le processus parent recupere lui a parir du bout de lecture du pipe le
// resultat de la cmd1 et l'utilise comme entree standard pour l'execution
// de la cmd2. Il dirige le resultat de la cmd2 dans le file2
void	parent_part(int file2, int *fd, char **envp, char **argv)
{
	char	**cmd_arg;
	char	**paths;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_arg = ft_split(argv[3], ' ');
	paths = find_cmd_paths(envp);
	//REDIRECTION
	dup2(fd[0], STDIN_FILENO);// L'entree standard de la cmd2 est le pipe avec le resultat de l'execution de cmd1
	dup2(file2, STDOUT_FILENO);//La sortie standard de la cmd2 est file2
	close(fd[1]);// Fermer le bout d'ecriture du pipe que l'on utilise pas
	//TEST EXECUTION AVEC EXECVE Avec chaque PATH
	while (paths[i])
	{

		cmd_path = ft_join(paths[i], cmd_arg[0]);
		execve(cmd_path, cmd_arg, envp);
		free(cmd_path);
		i++;
	}
	close(fd[0]);
}

void	pipex(int file1, int file2, char **envp, char **argv)
{
	int	fd[2];
	int status;
	pid_t	pid;

	if (pipe(fd) < 0)
		perror("Error");
	pid = fork();
	if (pid < 0)
		perror("Error");
	if (pid == 0)
	{
		//child process
		// printf("JE suis le processus fils\n");
		child_part(file1, fd, envp, argv);
		printf("JE suis le processus fils\n");// ????
	}
	else
	{
		// Dad_part
		wait(&status);
		parent_part(file2, fd, envp, argv);
		printf("Je suis le pere et jai du attendre mon fils\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	file1;
	int	file2;

	if (argc == 5)
	{
		file1 = open(argv[1], O_RDONLY);
		file2 = open(argv[4], O_CREAT |O_TRUNC | O_WRONLY, 0744); // ++ O_TRUNC
		if (file1 == -1 || file2 == -1)
			return (-1);
		pipex(file1, file2, envp, argv);
		close(file1);
		close(file2);
	}
	return (0);
}


/*
	Pipe()
		Fork() (creation d'un processus fils)
			child (executer la cmd1)
				dup2 pour rediriger
				close end[0]
				execve(cmd1)
			parent ou child 2 (executer cmd2)
				dup2
				close end[1]
				execve(cmd2)
Dans le processus fils on veut que stdin soit rediriger vers file1 (donc que notre fichier soit l'input de la cmd1)
Et que end[1] soit le stdout de la cmd1 (on veut ecrire le resultat dans notre pipe)
Dans le processus Parent ou child2, on veut que le stdin soit rediriger vers end[0] (on veut que le resultat de la cmd1 ecris dans le pipe soit linput de la cmd2)
Et que stdout soit rediriger vers file2 (on veut ecrire le resultat de la cmd2 dans file2)

PATH=/mnt/nfs/homes/clbernar/bin:/mnt/nfs/homes/clbernar/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
*/
// printf("%d",execve("/usr/bin/ls", tab, envp)); La ca marche
