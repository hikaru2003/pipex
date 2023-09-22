/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:25:59 by hmorisak          #+#    #+#             */
/*   Updated: 2023/02/27 18:04:24 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	to_hexa(unsigned long long num, char *str, int *len)
{
	unsigned long long	div;
	unsigned long long	mod;

	div = num / 16;
	mod = num % 16;
	if (div > 0)
		to_hexa(div, str, len);
	write(1, &str[mod], 1);
	(*len)++;
}
