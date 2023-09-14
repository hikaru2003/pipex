/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:27:29 by hmorisak          #+#    #+#             */
/*   Updated: 2023/02/27 18:04:09 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putchar(char c, int *len)
{
	write (1, &c, sizeof(char));
	(*len)++;
}

void	ft_putstr(char *s, int *len)
{
	size_t	slen;
	size_t	i;

	if (s)
	{
		slen = ft_strlen(s);
		i = 0;
		while (i < slen)
		{
			write(1, &s[i], sizeof(char));
			i++;
		}
		*len += (long)slen;
	}
	else
	{
		write(1, "(null)", 6);
		*len += 6;
	}
}

void	ft_putnbr(int n, int *len)
{
	long	num;
	long	quotient;
	long	mod;
	char	c;

	num = (long)n;
	if (n < 0)
	{
		num *= -1;
		write(1, "-", 1);
		(*len)++;
	}
	quotient = num / 10;
	mod = num % 10;
	if (quotient != 0)
		ft_putnbr((int)quotient, len);
	c = mod + '0';
	write(1, &c, sizeof(char));
	(*len)++;
}

void	ft_putnbr_u(unsigned int n, int *len)
{
	long	num;
	long	quotient;
	long	mod;
	char	c;

	num = (long)n;
	if (n < 0)
	{
		num *= -1;
		write(1, "-", 1);
		(*len)++;
	}
	quotient = num / 10;
	mod = num % 10;
	if (quotient != 0)
		ft_putnbr((unsigned int)quotient, len);
	c = mod + '0';
	write(1, &c, sizeof(char));
	(*len)++;
}
