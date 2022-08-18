/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 05:41:13 by mservage          #+#    #+#             */
/*   Updated: 2021/08/26 16:38:59 by mservage         ###   ########.fr       */
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
		if (fd->args == NULL || fd->args[0][0] == 0)
			ft_free_and_exit("Error\n", fd);
		if (dup2(fd->fd_in, 0) == -1 || dup2(fd->pipe[1], 1) == -1)
			ft_free_and_exit("Error\nDup2 failed\n", fd);
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
		if (fd->args == NULL || fd->args[0][0] == 0)
			ft_free_and_exit("Error\n", fd);
		if (dup2(fd->fd_out, 1) == -1 || dup2(fd->pipe[0], 0) == -1)
			ft_free_and_exit("Error\nDup2 failed\n", fd);
		close_all_fd(fd->fd_in, fd->fd_out, fd->pipe[0], fd->pipe[1]);
		define_path(fd);
	}
}

int	main(int ac, char **av, char *env[])
{
	t_fd	fd;

	if (env[0] == NULL)
	{
		printf("Error\nNo env\n");
		return (1);
	}
	check_main_arg(ac, av);
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
