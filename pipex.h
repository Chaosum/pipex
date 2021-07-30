/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:42:23 by matthieu          #+#    #+#             */
/*   Updated: 2021/07/30 16:09:02 by mservage         ###   ########.fr       */
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

int		main(int ac, char **av, char *env[]);
void	second_fork(t_fd *fd);
void	first_fork(t_fd *fd);
void	define_path(t_fd *fd);
char	*define_command_path(char *path, char *command, t_fd *fd);
void	init_struct_fd(t_fd *fd, char **av, char **env);
void	init_fd_pipe(t_fd *fd, char **av);
void	init_path(t_fd *fd);
void	check_main_arg(int ac);
void	ft_free_and_exit(char *msg, t_fd *fd);
void	ft_exit_error(char *msg, t_fd *fd);
int		close_all_fd(int fd, int fd2, int pipe_fd, int pipe_fd2);
void	ft_free_tab(char **tab);

#endif