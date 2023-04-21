/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:30:09 by clbernar          #+#    #+#             */
/*   Updated: 2023/04/21 11:55:47 by clbernar         ###   ########.fr       */
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
	char	*limiter;
	int		**pipe;
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

// Child_bonus
void	redirection(t_pipex *pipex, int index);
void	close_pipes(t_pipex *pipex, int index, int error_case);
void	child_bonus_error_case(t_pipex pipex, char **argv, int cas, int index);
void	child_process(t_pipex *pipex, char **envp, char **argv, int index);
void	pipex_fork_bonus(t_pipex *pipex, char **envp, char **argv);
// Pipex_bonus
void	init_struct(t_pipex *pipex, int argc, char **argv);
void	fill_here_doc(t_pipex *pipex);
char	**find_cmd_paths(char **envp);
char	*find_full_path(t_pipex pipex);
//Pipex_bonus_utils
void	free_double_char(char **tab);
void	free_double_int(int **tab, int tab_size);
void	error_messages(t_pipex pipex, char **argv, int cas, int index);
void	malloc_pipes(t_pipex *pipex);
char	*ft_join(char const *s1, char const *s2);

#endif
