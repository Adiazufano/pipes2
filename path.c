/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:53:16 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/06/19 11:42:18 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_command(char **path, char *command)
{
	int		j;
	char	*full_path;

	j = 0;
	while (path[j])
	{
		full_path = malloc(ft_strlen(path[j]) + ft_strlen(command) + 2);
		ft_strlcpy(full_path, path[j], ft_strlen(path[j]) + 2);
		ft_strlcat(full_path, "/", ft_strlen(path[j]) + 2);
		ft_strlcat(full_path, command, ft_strlen(command)
			+ ft_strlen(path[j]) + 2);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		j++;
	}
	return (ft_strdup(""));
}

char	*get_path(char *command, t_pipex *px)
{
	int		i;
	char	*path_env;
	char	**path;
	char	*result;

	i = 0;
	path_env = NULL;
	while (px->envp[i] && ft_strncmp(px->envp[i],
			"PATH=", ft_strlen("PATH=")) != 0)
		i++;
	if (!px->envp[i])
		return (NULL);
	path_env = px->envp[i] + 5;
	if (!*path_env)
		return (NULL);
	path = ft_split(path_env, ':');
	result = find_command(path, command);
	ft_free_split(path);
	return (result);
}

void	pipe_err(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	ft_free_split(char **split)
{
	int	index;

	index = 0;
	while (split[index])
	{
		free(split[index]);
		index++;
	}
	free(split);
}
