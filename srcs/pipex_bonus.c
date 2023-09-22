/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:29:56 by hmorisak          #+#    #+#             */
/*   Updated: 2023/03/27 20:41:37 by hmorisak         ###   ########.fr       */
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
	if (status == STDOUT && flag == 1)
		fd = open(file, (O_CREAT | O_WRONLY | O_APPEND), 0644);
	return (fd);
}

void	do_wait(int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		wait(NULL);
		i++;
	}
}

void	do_here_doc(int argc, char **argv, char **envp)
{
	int	outfile;
	int	flag;
	int	i;

	flag = 0;
	flag = here_doc(argv, argv[2], ft_strlen(argv[2]), envp);
	outfile = get_file(argv[argc - 1], STDOUT, flag);
	dup2(outfile, STDOUT);
	i = 4;
	pipex_here_doc(1, argc, argv, envp);
	while (i < argc - 1)
	{
		pipex_here_doc(i, argc, argv, envp);
		i++;
	}
	do_wait(argc - 4);
	unlink(".tmp.txt");
}

void	do_pipex(int argc, char **argv, char **envp)
{
	int	outfile;
	int	i;

	outfile = get_file(argv[argc - 1], STDOUT, 0);
	i = 3;
	dup2(outfile, STDOUT);
	pipex(1, argc, argv, envp);
	while (i < argc - 1)
	{
		pipex(i, argc, argv, envp);
		i++;
	}
	do_wait(argc - 3);
}

int	main(int argc, char *argv[], char **envp)
{
	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 9) == 0)
			do_here_doc(argc, argv, envp);
		else
			do_pipex(argc, argv, envp);
	}
	else
		ft_printf("Invalid number of argments.\n");
	return (0);
}
