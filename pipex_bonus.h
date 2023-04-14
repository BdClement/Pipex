/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:30:09 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/14 16:55:15 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "./Libft/Includes/libft.h"
# include "./Libft/Includes/get_next_line.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_pipex
{
	int		here_doc;
	char	*LIMITER;
	int		**pipe; // Tableau A VOIR n'utiliser qu'un simple pointeur *pipe
	int		nb_pipe;
	int		infile;
	int		outfile;
	int		nb_cmd;
	int		cmd_start;
	char	**all_paths;
	char	**cmd_args;
	char	*cmd_path;
	pid_t	pid;
}				t_pipex;

// NEW //
void	init_struct(t_pipex *pipex, int argc, char **argv);
void	fill_here_doc(t_pipex pipex);
// MANDATORY //
char	**find_cmd_paths(char **envp);
void	pipex_fork_bonus(t_pipex *pipex, char **envp, char **argv);
char	*ft_join(char const *s1, char const *s2);
void	child1(t_pipex pipex, char **envp, char **argv);
void	child2(t_pipex pipex, char **envp, char **argv);
void	free_double_char(char **tab);
char	*find_full_path(t_pipex pipex);
void	child1_error_case(t_pipex pipex, char **argv, int cas);
void	child2_error_case(t_pipex pipex, char **argv, int cas);

#endif
