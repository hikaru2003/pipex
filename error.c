/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:47:08 by hmorisak          #+#    #+#             */
/*   Updated: 2023/03/22 19:47:18 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_get_file_error(char *err_msg, char *file)
{
	write(STDERR, "zsh: ", 5);
	write(STDERR, err_msg, ft_strlen(err_msg));
	write(STDERR, ": ", 2);
	write(STDERR, file, ft_strlen(file));
	write(STDERR, "\n", 1);
}
