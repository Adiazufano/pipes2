/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:12:40 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/13 14:55:05 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmaeb, size_t size)
{
	unsigned char	*array;
	size_t			i;

	if (size != 0 && nmaeb >= __SIZE_MAX__ / size)
		return (NULL);
	array = malloc(nmaeb * size);
	if (!array)
		return (NULL);
	i = 0;
	while (i < nmaeb * size)
	{
		array[i++] = '\0';
	}
	return (array);
}
