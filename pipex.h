/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:26:20 by clbernar          #+#    #+#             */
/*   Updated: 2023/03/22 18:13:39 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>

char	**find_cmd_paths(char **envp);
void	pipex(int file1, int file2, char **envp, char **argv);
char	*ft_join(char const *s1, char const *s2);
void	child_part(int file1, int *fd, char **envp, char **argv);

#endif
