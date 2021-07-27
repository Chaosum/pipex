/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matthieu <matthieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 10:39:14 by matthieu          #+#    #+#             */
/*   Updated: 2021/07/26 14:33:47 by matthieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*define_command_path(char *path, char *command)
{
	char	*dest;
	int		i;
	int		j;

	dest = ft_calloc(ft_strlen(path) + ft_strlen(command) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (path[i])
	{
		dest[j] = path[i];
		j++;
		i++;
	}
	i = 0;
	while (command[i] != ' ' && command[i] != 0)
	{
		dest[j] = command[i];
		j++;
		i++;
	}
	return (dest);
}

void	first_fork(char **av, int fd[2], int pipe_fd[2])
{
	char	**args;

	args = ft_split(av[2], ' ');
	dup2(fd[0], 0);
	dup2(pipe_fd[1], 1);
	av[2] = define_command_path("/bin/", av[2]);
	close(fd[0]);
	close(fd[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(execve(av[2], args, NULL));
	return ;
}

void	second_fork(char **av, int fd[2], int pipe_fd[2])
{
	char	**args;

	dup2(fd[1], 1);
	dup2(pipe_fd[0], 0);
	args = ft_split(av[3], ' ');
	av[3] = define_command_path("/bin/", av[3]);
	close(fd[0]);
	close(fd[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(execve(av[3], args, NULL));
	return ;
}

int	close_all_fd(int fd[2], int pipe_fd[2])
{
	close(fd[0]);
	close(fd[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}

int	main(int ac, char **av)
{
	int		fd[2];
	int		pipe_fd[2];
	pid_t	pid[2];
	int		wstatus;

	if (ac < 5)
		return ((int)write(1, "Wrong args\n", 12));
	else if (ac > 5)
		return (0);
	fd[0] = open(av[1], O_RDWR);
	fd[1] = open(av[4], O_RDWR);
	pipe(pipe_fd);
	if (pipe_fd[0] < 0 || pipe_fd[1] < 0 || fd[0] < 0 || fd[1] < 0)
		return (close_all_fd(fd, pipe_fd));
	pid[0] = fork();
	if (pid[0] == 0)
		first_fork(av, fd, pipe_fd);
	pid[1] = fork();
	if (pid[1] == 0)
		second_fork(av, fd, pipe_fd);
	close_all_fd(fd, pipe_fd);
	waitpid(pid[0], &wstatus, 0);
	waitpid(pid[1], &wstatus, 0);
	return (0);
}
