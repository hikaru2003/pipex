/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:07:34 by hmorisak          #+#    #+#             */
/*   Updated: 2023/04/29 19:53:36 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int i, int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pipefd[2];

	if (i != 1 && is_cmd(argv[i], envp) == -1)
		return ;
	pipe(pipefd);
	pid = fork();
	if (pid < 0)
	{
		perror("zsh: fork failed");
		exit(1);
	}
	if (pid == 0 && i == 1)
		first_child(i, argv, pipefd, envp);
	else if (pid == 0 && i == argc - 2)
		last_chile(argv[i], pipefd, envp);
	else if (pid == 0)
		middle_child(argv[i], pipefd, envp);
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
}

void	exec(char *argv, char **envp)
{
	char	**cmd;
	char	**path;
	char	*filepath;

	cmd = ft_split(argv, ' ');
	path = get_path(envp);
	filepath = check_path(cmd, path);
	ft_free(path);
	if (execve(filepath, cmd, envp) == -1)
	{
		perror("execve error");
		exit(127);
	}
}

void	first_child(int i, char **argv, int *pipefd, char **envp)
{
	int	infile;

	if (get_file(argv[1], STDIN, 0) == -1 || is_cmd(argv[i + 1], envp) == -1)
		exit(1);
	infile = get_file(argv[1], STDIN, 0);
	if (infile != -1)
	{
		close(pipefd[0]);
		dup2(infile, STDIN);
		dup2(pipefd[1], 1);
		close(infile);
		close(pipefd[1]);
	}
	else
	{
		close(infile);
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		exit(1);
	}
	exec(argv[i + 1], envp);
}

void	last_chile(char *argv, int *pipefd, char **envp)
{
	close(pipefd[0]);
	close(pipefd[1]);
	exec(argv, envp);
}

void	middle_child(char *argv, int *pipefd, char **envp)
{
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	exec(argv, envp);
}
