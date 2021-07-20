#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

typedef struct s_pipex
{
	int			error_code;
	char		**a;
	char		**b;
	pid_t		pid;
}				t_pipex;

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);
void	ft_bzero(void *s, size_t n);
int		ft_isalpha(int c);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strnew(size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
void	pipex_close(int code, t_pipex *pipex);
void	pipex_init(t_pipex *pipex);
void	free_arr(char **str);
void	pipex_parent(t_pipex *pipex, int pfd[], char **av, char **envp);
void	pipex_child(t_pipex *pipex, int pfd[], char **av, char **envp);
#endif