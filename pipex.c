/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:38:24 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/06/18 14:48:12 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	command_not_found(char *path, char **args, int fd1, int fd2, int fd3)
{
	write(2, args[0], ft_strlen(args[0]));
	write(2, ": command not found\n", 20);
	ft_free_split(args);
	free(path);
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	if (fd3 >= 0)
		close(fd3);
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

pid_t	first_command(t_pipex *px, int infile, int oufile, int pipe_fd[2])
{
	pid_t pid;
	char *path;
	char **split;

	pid = fork();
	if (pid == 0)
	{

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
			command_not_found(path, split, pipe_fd[0], pipe_fd[1], infile);
		}
		execve(path, split, px -> envp);
		perror("execv");
		ft_free_split(split);
		free(path);
		exit(1);
	}
	return (pid);
}
pid_t	last_command(t_pipex *px, int outfile, int infile, int pipe_fd[2])
{
	pid_t pid;
	char *path;
	char **split;

	pid = fork();
	if (pid == 0)
	{
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
			command_not_found(path, split, pipe_fd[0], pipe_fd[1], outfile);
		}
		execve(path, split, px -> envp);
		perror("execve");
		ft_free_split(split);
		free(path);
		exit(1);
	}
	return(pid);
}
void	run_pipex(t_pipex *px)
{
	int	pipe_fd[2];
	int	infile;
	int	outfile;
	pid_t pid1;
	pid_t pid2;
	

	infile = open(px -> argv[1], O_RDONLY);
	check_split(px);
	if (infile == -1)
	{
		perror(px->argv[1]);
		outfile = open(px->argv[px->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
		{
			perror(px->argv[px->argc - 1]);
			exit(EXIT_FAILURE);
		}
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			close(outfile);
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]); // Cerramos escritura para que el segundo comando lea EOF
		// Ejecutar solo el segundo comando, el "last_command"
		pid2 = last_command(px, outfile, infile, pipe_fd);
		close(pipe_fd[0]);
		close(outfile);
		waitpid(pid2, NULL, 0);
		return ;
	}
	outfile = open(px -> argv[px -> argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		perror(px -> argv[px -> argc -1]);
		if (infile >= 0)
			close(infile);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}

	pid1 = first_command(px, infile, outfile, pipe_fd);
	pid2 = last_command(px, outfile, infile, pipe_fd);

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(infile);
	close(outfile);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
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
	run_pipex(&px);
	return (0);
}