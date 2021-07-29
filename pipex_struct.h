/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservage <mservage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 05:43:16 by mservage          #+#    #+#             */
/*   Updated: 2021/07/29 06:45:32 by mservage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_STRUCT_H
# define PIPEX_STRUCT_H

# include "pipex.h"

typedef struct s_fd
{
	int		fd_in;
	int		fd_out;
	int		pipe[2];
	pid_t	pid[2];
	char	**env;
	char	**av;
	char	**path;
	char	**args;
	int		wstatus;
}			t_fd;

#endif