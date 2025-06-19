/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:32:11 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/06/19 13:26:34 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "printf/ft_printf.h"
# include "sys/wait.h"

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		exit_status;
}				t_pipex;
char	**split_pipex(char *str);
char	*get_path(char *command, t_pipex *px);
int		open_infile(t_pipex *px);
int		open_outfile(t_pipex *px);
void	create_pipe(int pipe_fd[2]);
pid_t	first_command(t_pipex *px, int infile, int oufile, int pipe_fd[2]);
pid_t	last_command(t_pipex *px, int outfile, int infile, int pipe_fd[2]);
void	command_not_found(char *path, char **args);
void	check_split(t_pipex *px);
int		handle_infile_error(t_pipex *px, int outfile);
int		run_last_child(t_pipex *px, int outfile, int infile, int pipe_fd[2]);
void	run_first_child(t_pipex *px, int infile, int oufile, int pipe_fd[2]);
void	pipe_err(int *fd);
void	ft_free_split(char **split);
void	command_not_found(char *path, char **args);
#endif