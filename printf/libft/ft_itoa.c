/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:25:11 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/21 08:48:09 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digits(long nb)
{
	int	cont;

	cont = 1;
	if (nb < 0)
	{
		nb = -nb;
		cont++;
	}
	while (nb >= 10)
	{
		nb /= 10;
		cont++;
	}
	return (cont);
}

void	int_to_arr(char *nums, long nb, int cont, int neg)
{
	if (neg)
		nums[0] = '-';
	while (nb)
	{
		nums[--cont] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		cont;
	char	*nums;
	int		neg;
	long	nb;

	nb = (long)n;
	if (nb == 0)
		return (ft_strdup("0"));
	neg = 0;
	cont = count_digits(nb);
	if (nb < 0)
	{
		neg = 1;
		nb = -nb;
	}
	nums = malloc((cont + 1));
	if (!nums)
		return (NULL);
	nums[cont] = '\0';
	int_to_arr(nums, nb, cont, neg);
	return (nums);
}
