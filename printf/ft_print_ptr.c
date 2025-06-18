/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:22:47 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/25 19:48:51 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_ptr(unsigned long num, int *count)
{
	if (num == 0)
	{
		ft_putstr_fd("(nil)", 1);
		(*count) += 5;
		return ;
	}
	ft_putstr_fd("0x", 1);
	(*count) += 2;
	ft_putnbr_hex(num, count, 'p');
}
