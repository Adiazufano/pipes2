/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:20:07 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/25 20:09:54 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_unsigned_int(unsigned int num, int *count)
{
	if (num >= 10)
		ft_unsigned_int(num / 10, count);
	ft_putchar_fd((num % 10) + '0', 1);
	(*count)++;
}
