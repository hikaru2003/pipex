/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:24:18 by hmorisak          #+#    #+#             */
/*   Updated: 2023/04/29 20:40:48 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		perror("path not found");
		exit(1);
	}
	return (ft_split(envp[i] + 5, ':'));
}

char	*check_path(char **cmd, char **path)
{
	char	*path_slash;
	char	*filepath;
	int		i;

	if (access(cmd[0], X_OK) == 0)
		return (ft_strjoin(cmd[0], ""));
	i = 0;
	while (path[i])
	{
		path_slash = ft_strjoin(path[i], "/");
		filepath = ft_strjoin(path_slash, cmd[0]);
		gnl_free(&path_slash);
		if (access(filepath, X_OK) == 0)
			return (filepath);
		gnl_free(&filepath);
		i++;
	}
	return (NULL);
}

int	is_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	**path;
	char	*filepath;

	cmd = ft_split(argv, ' ');
	path = get_path(envp);
	filepath = check_path(cmd, path);
	ft_free(path);
	if (filepath == NULL || all_space(argv) == 0)
	{
		gnl_free(&filepath);
		write(STDERR, "zsh: command not found: ", 24);
		if (all_space(argv) == 0)
			write(STDERR, argv, ft_strlen(argv));
		else
			write(STDERR, cmd[0], ft_strlen(cmd[0]));
		write(STDERR, "\n", 1);
		ft_free(cmd);
		return (-1);
	}
	ft_free(cmd);
	gnl_free(&filepath);
	return (0);
}

int	all_space(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
