/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:15:46 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/25 20:11:08 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_str(va_list args, int *count)
{
	char	*s;

	s = va_arg(args, char *);
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		(*count) += 6;
		return ;
	}
	ft_putstr_fd(s, 1);
	(*count) += ft_strlen(s);
}
