/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:26:20 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/04 20:40:04 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_pipex
{
	int		pipe[2];
	int		infile;
	int		outfile;
	char	**all_paths;
	char	**cmd_args;
	char	*cmd_path;
	pid_t	pid1;
	pid_t	pid2;

}				t_pipex;

char	**find_cmd_paths(char **envp);
void	pipex_fork(t_pipex *pipex, char **envp, char **argv);
char	*ft_join(char const *s1, char const *s2);
void	child1(t_pipex pipex, char **envp, char **argv);
void	child2(t_pipex pipex, char **envp, char **argv);
void	free_double_char(char **tab);
char	*find_full_path(t_pipex pipex);
void	child1_error_case(t_pipex pipex, char **argv, int cas);
void	child2_error_case(t_pipex pipex, char **argv, int cas);

#endif
