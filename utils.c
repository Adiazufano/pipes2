/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:20:31 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/06/19 13:20:41 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(t_pipex *px)
{
	int	infile;

	infile = open(px -> argv[1], O_RDONLY);
	if (infile == -1)
		perror(px -> argv[1]);
	return (infile);
}

int	open_outfile(t_pipex *px)
{
	int	outfile;

	outfile = open(px -> argv[px -> argc - 1],
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile == -1)
		perror(px -> argv[px -> argc - 1]);
	return (outfile);
}

void	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

pid_t	first_command(t_pipex *px, int infile, int oufile, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		run_first_child(px, infile, oufile, pipe_fd);
	return (pid);
}

pid_t	last_command(t_pipex *px, int outfile, int infile, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		run_last_child(px, outfile, infile, pipe_fd);
	return (pid);
}
