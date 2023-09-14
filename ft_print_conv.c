/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:14:25 by hmorisak          #+#    #+#             */
/*   Updated: 2023/02/27 18:03:59 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_print_p(unsigned long long args, int *len)
{
	write(1, "0x", 2);
	*len += 2;
	to_hexa(args, "0123456789abcdef", len);
}

static void	ft_print_x(unsigned int args, char conversion, int *len)
{
	if (conversion == 'x')
		to_hexa(args, "0123456789abcdef", len);
	if (conversion == 'X')
		to_hexa(args, "0123456789ABCDEF", len);
}

static void	ft_print_u(unsigned int num, int *len)
{
	ft_putnbr_u(num, len);
}

void	print_conv(const char *format, va_list *args, int *len)
{
	char	conversion;

	conversion = *(++format);
	if (conversion == 'c')
		ft_putchar(va_arg(*args, int), len);
	if (conversion == 's')
		ft_putstr(va_arg(*args, char *), len);
	if (conversion == 'p')
		ft_print_p(va_arg(*args, unsigned long long), len);
	if (conversion == 'd' || conversion == 'i')
		ft_putnbr(va_arg(*args, int), len);
	if (conversion == 'u')
		ft_print_u(va_arg(*args, unsigned int), len);
	if (conversion == 'x' || conversion == 'X')
		ft_print_x(va_arg(*args, unsigned int), conversion, len);
	if (conversion == '%')
	{
		write(1, "%", 1);
		(*len)++;
	}
}
