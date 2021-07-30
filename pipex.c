/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 05:41:13 by mservage          #+#    #+#             */
/*   Updated: 2021/07/30 16:02:57 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_fork(t_fd *fd)
{
	fd->pid[0] = fork();
	if (fd->pid[0] < 0)
		ft_free_and_exit("First fork error\n", fd);
	if (fd->pid[0] == 0)
	{
		fd->args = ft_split(fd->av[2], ' ');
		if (fd->args == NULL)
			ft_free_and_exit("Malloc error\n", fd);
		dup2(fd->fd_in, 0);
		dup2(fd->pipe[1], 1);
		close_all_fd(fd->fd_in, fd->fd_out, fd->pipe[0], fd->pipe[1]);
		define_path(fd);
	}
}

void	second_fork(t_fd *fd)
{
	fd->pid[1] = fork();
	if (fd->pid[1] < 0)
		ft_free_and_exit("Second fork error\n", fd);
	if (fd->pid[1] == 0)
	{
		fd->args = ft_split(fd->av[3], ' ');
		if (fd->args == NULL)
			ft_free_and_exit("Malloc error\n", fd);
		dup2(fd->fd_out, 1);
		dup2(fd->pipe[0], 0);
		close_all_fd(fd->fd_in, fd->fd_out, fd->pipe[0], fd->pipe[1]);
		define_path(fd);
	}
}

int	main(int ac, char **av, char *env[])
{
	t_fd	fd;

	check_main_arg(ac);
	init_struct_fd(&fd, av, env);
	init_fd_pipe(&fd, av);
	first_fork(&fd);
	second_fork(&fd);
	close_all_fd(fd.fd_in, fd.fd_out, fd.pipe[0], fd.pipe[1]);
	ft_free_tab(fd.path);
	waitpid(fd.pid[0], NULL, 0);
	waitpid(fd.pid[1], &(fd.wstatus), 0);
	if (WIFEXITED(fd.wstatus))
		return (WEXITSTATUS(fd.wstatus));
	return (1);
}
