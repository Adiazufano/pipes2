/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:38:24 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/06/19 13:25:24 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_first_child(t_pipex *px, int infile, int oufile, int pipe_fd[2])
{
	char	*path;
	char	**split;

	split = split_pipex(px -> argv[2]);
	dup2(infile, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(infile);
	path = get_path(split[0], px);
	if (!path || access(path, X_OK) != 0)
	{
		close(oufile);
		command_not_found(path, split);
	}
	execve(path, split, px -> envp);
	perror("execv");
	ft_free_split(split);
	free(path);
	exit(1);
}

int	run_last_child(t_pipex *px, int outfile, int infile, int pipe_fd[2])
{
	char	**split;
	char	*path;

	split = split_pipex(px -> argv[px -> argc - 2]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(outfile);
	path = get_path(split[0], px);
	if (!path || access(path, X_OK) != 0)
	{
		close(infile);
		command_not_found(path, split);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(outfile);
	}
	execve(path, split, px -> envp);
	perror("execve");
	ft_free_split(split);
	free(path);
	exit(1);
}

static int	run_normal_pipex(t_pipex *px, int infile, int outfile)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status2;

	create_pipe(pipe_fd);
	pid1 = first_command(px, infile, outfile, pipe_fd);
	pid2 = last_command(px, outfile, infile, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(infile);
	close(outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	else
		return (0);
}

static int	run_pipex(t_pipex *px)
{
	int		infile;
	int		outfile;
	pid_t	pid1;
	int		pipe_fd[2];

	check_split(px);
	outfile = open_outfile(px);
	infile = open_infile(px);
	if (infile == -1 && outfile == -1)
		return (1);
	if (infile == -1)
		return (handle_infile_error(px, outfile));
	if (outfile == -1)
	{
		create_pipe(pipe_fd);
		pid1 = first_command(px, infile, outfile, pipe_fd);
		if (infile >= 0)
			close(infile);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	return (run_normal_pipex(px, infile, outfile));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	px;

	px.argc = argc;
	px.argv = argv;
	px.envp = envp;
	if (argc != 5 || !argv[1][0] || !argv[2][0] || !argv[3][0] || !argv[4][0])
	{
		ft_printf("No found word E/error, please, check it.\n");
		exit(1);
	}
	return (run_pipex(&px));
}
