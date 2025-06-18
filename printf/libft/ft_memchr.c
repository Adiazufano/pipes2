/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:26:02 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/13 14:56:54 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*convert;

	convert = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (convert[i] == (unsigned char)c)
		{
			return (convert + i);
		}
		i++;
	}
	return (NULL);
}
