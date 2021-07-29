/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 05:41:13 by mservage          #+#    #+#             */
/*   Updated: 2021/07/29 08:05:18 by mservage         ###   ########.fr       */
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
	write(1, msg, ft_strlen(msg));
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

void	init_path(t_fd *fd, char **env)
{
	int	fd_command[2];

	while (ft_strncmp(*(fd->env), "PATH=", 5))
		fd->env++;
	fd_command[0] = open(fd->av[2], O_RDONLY);
	fd_command[1] = open(fd->av[3], O_RDONLY);
	if (fd->env == NULL && (fd_command[0] < 0 || fd_command[1] < 0))
		ft_exit_error("No PATH variable\n", fd);
	close_all_fd(fd_command[0], fd_command[1], -1, -1);
	if (fd->env)
	{
		fd->path = ft_split(&(fd->env)[0][5], ':');
		if (fd->path == NULL)
			ft_exit_error("Malloc error in split\n", fd);
	}
}

void	init_fd_pipe(t_fd *fd, char **av)
{
	fd->fd_in = open(av[1], O_RDWR);
	if (fd->fd_in < 0)
		ft_exit_error("Infile open Error\n", fd);
	fd->fd_out = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd->fd_out < 0)
		ft_exit_error("Outfile open Error\n", fd);
	if (pipe(fd->pipe) == -1)
		ft_exit_error("Pipe creation Error\n", fd);
}

void	init_struct_fd(t_fd *fd, char **av, char **env)
{
	fd->env = env;
	fd->av = av;
	fd->wstatus = 0;
	fd->args = NULL;
	init_path(fd, env);
}

char	*define_command_path(char *path, char *command, t_fd *fd)
{
	char	*dest;
	int		i;
	int		j;

	dest = ft_calloc(ft_strlen(path) + ft_strlen(command) + 2, sizeof(char));
	i = 0;
	j = 0;
	if (dest == NULL)
		ft_free_and_exit("Malloc error\n", fd);
	while (path[i])
	{
		dest[j] = path[i];
		j++;
		i++;
	}
	dest[j++] = '/';
	i = 0;
	while (command[i] != ' ' && command[i] != 0)
	{
		dest[j] = command[i];
		j++;
		i++;
	}
	return (dest);
}

int	check_sh_file(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (i > 3)
		i = i - 3;
	else
		return (0);
	if (ft_strncmp(&file[i], ".sh", 3) == 0)
		return (1);
	return (0);
}

void	define_path(t_fd *fd)
{
	int		i;
	char	*command_path;

	i = 0;
	if (ft_strncmp(fd->args[0], "/", 1) == 0
		|| ft_strncmp(fd->args[0], "./", 2) == 0)
	{
		if (check_sh_file(*fd->args))
			execve("/bin/sh", fd->args, NULL);
		execve(fd->args[0], fd->args, NULL);
	}
	while (fd->path[i])
	{
		command_path = define_command_path(fd->path[i], fd->args[0], fd);
		execve(command_path, fd->args, NULL);
		i++;
		free(command_path);
	}
	ft_free_and_exit("Wrong command path\n", fd);
}

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
	waitpid(fd.pid[0], NULL, 0);
	waitpid(fd.pid[1], &(fd.wstatus), 0);
	if (WIFEXITED(fd.wstatus))
		return (WEXITSTATUS(fd.wstatus));
	return (1);
}
