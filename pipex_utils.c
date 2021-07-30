/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:00:34 by mservage          #+#    #+#             */
/*   Updated: 2021/07/30 16:00:59 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}

int	close_all_fd(int fd, int fd2, int pipe_fd, int pipe_fd2)
{
	if (fd > 0)
		close(fd);
	if (fd2 > 0)
		close(fd2);
	if (pipe_fd > 0)
		close(pipe_fd);
	if (pipe_fd2 > 0)
		close(pipe_fd2);
	return (1);
}

void	ft_exit_error(char *msg, t_fd *fd)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	close_all_fd(fd->fd_in, fd->fd_out, fd->pipe[0], fd->pipe[1]);
	exit(1);
}

void	ft_free_and_exit(char *msg, t_fd *fd)
{
	ft_free_tab(fd->path);
	ft_free_tab(fd->args);
	ft_exit_error(msg, fd);
}

void	check_main_arg(int ac)
{
	if (ac != 5)
	{
		write(1, "Wrong args\n", 12);
		exit(1);
	}
}
