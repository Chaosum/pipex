/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:42:23 by matthieu          #+#    #+#             */
/*   Updated: 2021/07/26 14:00:11 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <wait.h>
# include <fcntl.h>

char	*define_command_path(char *path, char *command);
void	first_fork(char **av, int fd[2], int pipe_fd[2]);
void	second_fork(char **av, int fd[2], int pipe_fd[2]);
int		close_all_fd(int fd[2], int pipe_fd[2]);
int		main(int ac, char **av);

#endif