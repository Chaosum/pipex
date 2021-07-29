// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pipex.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/07/02 10:39:14 by matthieu          #+#    #+#             */
// /*   Updated: 2021/07/29 05:35:33 by mservage         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "pipex.h"

// char	*define_path(char *command, char **env, int i)
// {
// 	char	**dest2;
// 	char	*temp;
// 	int		j;
// 	char	**temp_command;

// 	temp_command = ft_split(command, ' ');
// 	while (ft_strncmp(env[i], "PATH=", 5))
// 		i++;
// 	dest2 = ft_split(&env[i][5], ':');
// 	i = -1;
// 	while (dest2[++i])
// 	{
// 		temp = define_command_path(dest2[i], temp_command[0]);
// 		j = open(temp, O_RDONLY);
// 		if (j > 0)
// 		{
// 			close(j);
// 			break ;
// 		}
// 		close(j);
// 		free(temp);
// 	}
// 	ft_free_tab(temp_command);
// 	ft_free_tab(dest2);
// 	return (temp);
// }

// char	*define_command_path(char *path, char *command)
// {
// 	char	*dest;
// 	int		i;
// 	int		j;

// 	dest = ft_calloc(ft_strlen(path) + ft_strlen(command) + 2, sizeof(char));
// 	i = 0;
// 	j = 0;
// 	while (path[i])
// 	{
// 		dest[j] = path[i];
// 		j++;
// 		i++;
// 	}
// 	dest[j++] = '/';
// 	i = 0;
// 	while (command[i] != ' ' && command[i] != 0)
// 	{
// 		dest[j] = command[i];
// 		j++;
// 		i++;
// 	}
// 	return (dest);
// }

// void	first_fork(char **av, int fd[2], int pipe_fd[2], char **env)
// {
// 	char	**args;

// 	args = ft_split(av[2], ' ');
// 	av[2] = define_path(av[2], env, 0);
// 	dup2(fd[0], 0);
// 	dup2(pipe_fd[1], 1);
// 	close_all_fd(fd[0], fd[1], pipe_fd[0], pipe_fd[1]);
// 	exit(execve(av[2], args, NULL));
// 	return ;
// }

// void	second_fork(char **av, int fd[2], int pipe_fd[2], char **env)
// {
// 	char	**args;

// 	args = ft_split(av[3], ' ');
// 	av[3] = define_path(av[3], env, 0);
// 	dup2(fd[1], 1);
// 	dup2(pipe_fd[0], 0);
// 	close_all_fd(fd[0], fd[1], pipe_fd[0], pipe_fd[1]);
// 	exit(execve(av[3], args, NULL));
// 	return ;
// }

// int	main(int ac, char **av, char *env[])
// {
// 	int		fd[2];
// 	int		pipe_fd[2];
// 	pid_t	pid[2];
// 	int		wstatus;

// 	if (ac != 5)
// 		return ((int)write(1, "Wrong args\n", 12));
// 	if (open_fd_and_pipe(fd, pipe_fd, av))
// 		return (1);
// 	pid[0] = fork();
// 	if (pid[0] < 0)
// 		return (close_all_fd(fd[0], fd[1], pipe_fd[0], pipe_fd[1]));
// 	if (pid[0] == 0)
// 		first_fork(av, fd, pipe_fd, env);
// 	pid[1] = fork();
// 	if (pid[1] < 0)
// 		return (close_all_fd(fd[0], fd[1], pipe_fd[0], pipe_fd[1]));
// 	if (pid[1] == 0)
// 		second_fork(av, fd, pipe_fd, env);
// 	close_all_fd(fd[0], fd[1], pipe_fd[0], pipe_fd[1]);
// 	waitpid(pid[0], NULL, 0);
// 	waitpid(pid[1], &wstatus, 0);
// 	if (WIFEXITED(wstatus))
// 		return (WEXITSTATUS(wstatus));
// 	return (1);
// }
