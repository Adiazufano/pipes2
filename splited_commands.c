/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splited_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:51:57 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/06/16 18:33:19 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		if (str[i] == '\'' || str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\'' && str[i] != '\"')
				i++;
			if (str[i] == '\'' || str[i] == '\"')
				count++;
		}
		else if (str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
			count++;
		i++;
	}
	return (count);
}

static char	*extract_word(const char *str, int *i)
{
	int		start;
	char	quote;
	char	*word;

	if (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = str[*i];
		start = ++(*i);
		while (str[*i] && str[*i] != quote)
			(*i)++;
		word = ft_substr(str, start, *i - start);
		if (str[*i] == quote)
			(*i)++;
		return (word);
	}
	else
	{
		start = *i;
		while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '\"')
			(*i)++;
		return (ft_substr(str, start, *i - start));
	}
}

char	**split_pipex(char *str)
{
	char	**splited;
	int		j;
	int		i;

	j = 0;
	i = 0;
	splited = malloc(sizeof (char *) * (count_words(str) + 1));
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		splited[j++] = extract_word(str, &i);
	}
	splited[j] = NULL;
	return (splited);
}
