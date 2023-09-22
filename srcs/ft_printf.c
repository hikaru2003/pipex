/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:00:18 by hmorisak          #+#    #+#             */
/*   Updated: 2023/03/01 18:25:40 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdarg.h>

static void	write_loop(const char *format, va_list *args, int *len)
{
	while (*format != '\0')
	{
		if (*format == '%')
		{
			print_conv(format, args, len);
			format++;
		}
		else
		{
			write(1, format, 1);
			(*len)++;
		}
		format++;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, format);
	write_loop(format, &args, &len);
	va_end(args);
	return (len);
}

// int	main(void)
// {
// 	char	c;

// 	// printf("num=%d\n", ft_printf("%u\n", -11));
// 	// printf("num=%d\n", printf("%u\n", -11));
// 	ft_printf("%5%");
// 	// printf("%5%");
// 	// printf("num=%d\n", ft_printf("%X\n", LONG_MAX));
// 	// printf("num=%d\n", printf("%lX\n", LONG_MAX));
// 	// printf("num=%d\n", ft_printf("%p\n", &c));
// 	// printf("num=%d\n", printf("%p\n", &c));
// 	// printf("num=%d\n", ft_printf("%s\n", NULL));
// 	// printf("num=%d\n", printf("%s\n", NULL));
// 	return (0);
// }
