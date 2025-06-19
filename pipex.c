/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:38:24 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/06/18 18:49:30 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	command_not_found(char *path, char **args)
{
	write(2, args[0], ft_strlen(args[0]));
	if (!path)
		write(2, ": No such file or directory\n", 28);
	else
		write(2, ": command not found\n", 20);
	ft_free_split(args);
	free(path);
	exit(127);
}

void	check_split(t_pipex *px)
{
	char	**split;
	int		i;

	i = 2;
	while (i < px -> argc - 1)
	{
		split = split_pipex(px -> argv[i]);
		if (!split || !split[0])
		{
			ft_printf("No found word E/error, please, check it.\n");
			ft_free_split(split);
			exit(EXIT_FAILURE);
		}
		ft_free_split(split);
		i++;
	}
}

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

pid_t	first_command(t_pipex *px, int infile, int oufile, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		run_first_child(px, infile, oufile, pipe_fd);
	return (pid);
}

void	run_last_child(t_pipex *px, int outfile, int infile, int pipe_fd[2])
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

pid_t	last_command(t_pipex *px, int outfile, int infile, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		run_last_child(px, outfile, infile, pipe_fd);
	return (pid);
}

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

static void	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

static int	handle_infile_error(t_pipex *px)
{
	int		pipe_fd[2];
	int		outfile;
	pid_t	pid2;
	int		status2;

	outfile = open_outfile(px);
	if (outfile < 0)
		exit(1);
	create_pipe(pipe_fd);
	close(pipe_fd[1]);
	pid2 = last_command(px, outfile, -1, pipe_fd);
	close(pipe_fd[0]);
	close(outfile);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		return (WEXITSTATUS(status2));
	else
		return (0);
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

int	run_pipex(t_pipex *px)
{
	int	infile;
	int	outfile;

	check_split(px);
	infile = open_infile(px);
	if (infile == -1)
		return (handle_infile_error(px));
	outfile = open_outfile(px);
	if (outfile == -1)
	{
		if (infile >= 0)
			close(infile);
		exit(1);
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
