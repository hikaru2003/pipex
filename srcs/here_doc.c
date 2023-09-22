/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:20:16 by hmorisak          #+#    #+#             */
/*   Updated: 2023/03/22 20:16:17 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*is_env(char *buf, char *limiter, char **envp)
{
	char	**env;
	int		i;

	i = 0;
	if (!ft_strchr(limiter, '\"') && !ft_strchr(limiter, '\'') && *buf == '$')
	{
		while (envp[i])
		{
			env = ft_split(envp[i], '=');
			env[1] = ft_strjoin(env[1], "\n");
			if (ft_strncmp(&buf[1], env[0], ft_strlen(&buf[1]) - 1) == 0)
				return (env[1]);
			i++;
		}
	}
	return (buf);
}

int	here_doc(char **argv, char *limiter, int lmtlen, char **envp)
{
	int		fd;
	int		line_len;
	char	*buf;
	char	*line;

	line = (char *)malloc(1);
	if (!line)
		return (INT_MAX);
	fd = open(".tmp.txt", (O_CREAT | O_RDWR | O_TRUNC), 0644);
	while (1)
	{
		write(0, "> ", 2);
		buf = get_next_line(STDIN);
		if (!buf)
			break ;
		buf = is_env(buf, limiter, envp);
		line_len = ft_strlen(buf);
		if ((lmtlen == line_len - 1) && !ft_strncmp(buf, limiter, lmtlen))
			break ;
		line = gnl_strjoin(line, buf);
	}
	write(fd, line, ft_strlen(line));
	gnl_free(&line);
	argv[1] = ".tmp.txt";
	return (1);
}

void	pipex_here_doc(int i, int argc, char **argv, char **envp)
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
		first_child(i + 1, argv, pipefd, envp);
	else if (pid == 0 && i == argc - 2)
		last_chile(argv[i], pipefd, envp);
	else if (pid == 0 && i > 3)
		middle_child(argv[i], pipefd, envp);
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
}
