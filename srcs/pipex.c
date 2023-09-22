/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:29:56 by hmorisak          #+#    #+#             */
/*   Updated: 2023/04/05 15:27:48 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_file(char *file, int status, int flag)
{
	int	fd;

	if (status == STDIN)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			write_get_file_error(strerror(errno), file);
			return (-1);
		}
	}
	if (status == STDOUT && access(file, F_OK) == 0 && access(file, W_OK) == -1)
	{
		write_get_file_error(strerror(errno), file);
		exit (1);
	}
	if (status == STDOUT && flag == 0)
		fd = open(file, (O_CREAT | O_WRONLY | O_TRUNC), 0644);
	return (fd);
}

int	main(int argc, char *argv[], char **envp)
{
	int	outfile;

	if (argc == 5)
	{
		outfile = get_file(argv[argc - 1], STDOUT, 0);
		dup2(outfile, STDOUT);
		pipex(1, argc, argv, envp);
		pipex(3, argc, argv, envp);
		wait(NULL);
		wait(NULL);
	}
	else
		ft_printf("Invalid number of argments.\n");
	return (0);
}
