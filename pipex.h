/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:42:23 by matthieu          #+#    #+#             */
/*   Updated: 2021/07/29 07:43:03 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include "pipex_struct.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

// char	*define_path(char *command, char **env, int i);
// char	*define_command_path(char *path, char *command);
// void	first_fork(char **av, int fd[2], int pipe_fd[2], char **env);
// void	second_fork(char **av, int fd[2], int pipe_fd[2], char **env);
// int		main(int ac, char **av, char *env[]);
// int		close_all_fd(int fd, int fd2, int pipe_fd, int pipe_fd2);
// void	ft_free_tab(char **tab);
// int		open_fd_and_pipe(int fd[2], int pipe_fd[2], char **av);

int		main(int ac, char **av, char *env[]);
void	second_fork(t_fd *fd);
void	first_fork(t_fd *fd);
void	define_path(t_fd *fd);
int		check_sh_file(char *file);
char	*define_command_path(char *path, char *command, t_fd *fd);
void	init_struct_fd(t_fd *fd, char **av, char **env);
void	init_fd_pipe(t_fd *fd, char **av);
void	init_path(t_fd *fd, char **env);
void	check_main_arg(int ac);
void	ft_free_and_exit(char *msg, t_fd *fd);
void	ft_exit_error(char *msg, t_fd *fd);
int		close_all_fd(int fd, int fd2, int pipe_fd, int pipe_fd2);
void	ft_free_tab(char **tab);

#endif