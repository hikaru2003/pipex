/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:30:00 by hmorisak          #+#    #+#             */
/*   Updated: 2023/03/22 20:11:13 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <errno.h>
# include <libc.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h> //pid_t fork(void);
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h> 
# include <limits.h>
//pid_t waitpid(pid_t pid, int *status_ptr, int options);

# define STDIN 0
# define STDOUT 1
# define STDERR 2

//error.c
void	write_get_file_error(char *err_msg, char *file);
//free.c
char	*ft_free(char **str);
//ft_print_conv.c
void	print_conv(const char *format, va_list *args, int *len);
//ft_printf.c
int		ft_printf(const char *format, ...);
//ft_put.c
void	ft_putchar(char c, int *len);
void	ft_putstr(char *s, int *len);
void	ft_putnbr(int n, int *len);
void	ft_putnbr_u(unsigned int n, int *len);
//ft_split.c
char	**ft_split(char const *s, char c);
//get_next_line_utils.c
char	*ft_strchr(const char *s, int c);
char	*gnl_free(char **str);
char	*gnl_strjoin(char *line, char *buf);
//ft_strjoin.c
char	*ft_strjoin(char const *s1, char const *s2);
//get_next_line.c
char	*get_next_line(int fd);
//here_doc.c
char	*is_env(char *buf, char *limiter, char **envp);
int		here_doc(char **argv, char *limiter, int lmtlen, char **envp);
void	pipex_here_doc(int i, int argc, char **argv, char **envp);
//path.c
char	**get_path(char **envp);
char	*check_path(char **cmd, char **path);
int		is_cmd(char *argv, char **envp);
int		all_space(char *argv);
//pipe_tool.c
void	pipex(int i, int argc, char **argv, char **envp);
void	exec(char *argv, char **envp);
void	first_child(int i, char **argv, int *pipefd, char **envp);
void	last_chile(char *argv, int *pipefd, char **envp);
void	middle_child(char *argv, int *pipefd, char **envp);
//pipex_bonus.c
int		get_file(char *file, int status, int flag);
void	do_wait(int count);
void	do_here_doc(int argc, char **argv, char **envp);
void	do_pipex(int argc, char **argv, char **envp);
//pipex.c
int		get_file(char *file, int status, int flag);
//to_hexa.c
void	to_hexa(unsigned long long num, char *str, int *len);
//tool.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *c);

#endif