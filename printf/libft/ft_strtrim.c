/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:34:59 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/16 20:48:43 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*arr;
	size_t	len;
	size_t	start;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	start = 0;
	while (s1[start] != '\0' && ft_strchr((char *)set, s1[start]) != NULL)
		start++;
	while (len > start && ft_strchr((char *)set, s1[len - 1]) != NULL)
		len--;
	arr = (char *)malloc((len - start + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, (char *) s1 + start, len - start + 1);
	return (arr);
}
