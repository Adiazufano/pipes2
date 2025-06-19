/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:20:11 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/06/19 13:20:15 by aldiaz-u         ###   ########.fr       */
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

int	handle_infile_error(t_pipex *px, int outfile)
{
	int		pipe_fd[2];
	pid_t	pid2;
	int		status2;

	if (outfile == -1)
		return (1);
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
