// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   utils.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/07/29 04:10:47 by mservage          #+#    #+#             */
// /*   Updated: 2021/07/29 07:42:49 by mservage         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "pipex.h"



// int	close_all_fd(int fd, int fd2, int pipe_fd, int pipe_fd2)
// {
// 	if (fd > 0)
// 		close(fd);
// 	if (fd2 > 0)
// 		close(fd2);
// 	if (pipe_fd > 0)
// 		close(pipe_fd);
// 	if (pipe_fd2 > 0)
// 		close(pipe_fd2);
// 	return (1);
// }

// int	open_fd_and_pipe(int fd[2], int pipe_fd[2], char **av)
// {
// 	fd[0] = open(av[1], O_RDWR);
// 	fd[1] = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
// 	pipe(pipe_fd);
// 	if (pipe_fd[0] < 0 || pipe_fd[1] < 0 || fd[0] < 0 || fd[1] < 0)
// 	{
// 		write(1, "Open error\n", 12);
// 		close_all_fd(fd[0], fd[1], pipe_fd[0], pipe_fd[1]);
// 		return (1);
// 	}
// 	return (0);
// }
