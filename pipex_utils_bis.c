/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:02:14 by mservage          #+#    #+#             */
/*   Updated: 2021/07/30 16:09:16 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_path(t_fd *fd)
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
	init_path(fd);
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

void	define_path(t_fd *fd)
{
	int		i;
	char	*command_path;

	i = 0;
	if (ft_strncmp(fd->args[0], "/", 1) == 0
		|| ft_strncmp(fd->args[0], "./", 2) == 0)
		execve(fd->args[0], fd->args, NULL);
	while (fd->path[i])
	{
		command_path = define_command_path(fd->path[i], fd->args[0], fd);
		execve(command_path, fd->args, NULL);
		i++;
		free(command_path);
	}
	ft_free_and_exit("Wrong command path\n", fd);
}
