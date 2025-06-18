/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:31:15 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/09 17:09:13 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	resultado;
	int	count;
	int	sign;

	resultado = 0;
	count = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	while (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		count++;
		nptr++;
	}
	if (count > 1)
		return (0);
	while (*nptr >= '0' && *nptr <= '9')
	{
		resultado = resultado * 10 + (*nptr - '0');
		nptr++;
	}
	return (resultado * sign);
}
