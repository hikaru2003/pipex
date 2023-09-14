/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:15:52 by hmorisak          #+#    #+#             */
/*   Updated: 2023/03/18 19:28:17 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*do_it(char *line, char	**save, int fd)
{
	ssize_t	ret;
	char	*buf;

	line[0] = '\0';
	if (*save && **save)
		line = ft_strjoin(line, *save);
	ret = 1;
	while (ret > 0 && !ft_strchr(line, '\n'))
	{
		buf = (char *)malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (gnl_free(&line));
		ret = read(fd, buf, BUFFER_SIZE);
		if (line[0] == '\0' && ret == 0)
			break ;
		buf[ret] = '\0';
		line = ft_strjoin(line, buf);
		gnl_free(&buf);
		ret = 1;
	}
	if (*save != NULL)
		gnl_free(save);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*pt;
	static char	*save;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(1);
	if (!line)
		return (NULL);
	line = do_it(line, &save, fd);
	if (!line)
		return (NULL);
	if (line[0] == '\0')
		return (gnl_free(&line));
	if (line && ft_strchr(line, '\n'))
	{
		pt = ft_strchr(line, '\n') + 1;
		save = (char *)malloc(1);
		if (!save)
			return (gnl_free(&line));
		save[0] = '\0';
		save = ft_strjoin(save, pt);
		*pt = '\0';
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*buf;

// 	fd = open("test.txt", O_RDONLY);
// 	close(fd);
// 	// printf("%d\n", fd);
// 	while (1)
// 	{
// 		buf = get_next_line(fd);
// 		printf("%s", buf);
// 		free(buf);
// 		if (!buf)
// 			break ;
// 	}
// 	// system("leaks a.out");
// 	return (0);
// }
