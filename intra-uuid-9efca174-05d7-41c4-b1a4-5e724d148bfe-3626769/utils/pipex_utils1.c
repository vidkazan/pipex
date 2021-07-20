#include "pipex.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
			ft_putchar_fd(*s++, fd);
	}
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	symbol;

	symbol = c;
	while (*s)
	{
		if (*s == symbol)
			return ((void *)s);
		s++;
	}
	if (*s == symbol && symbol == 0)
		return ((void *)s);
	return (NULL);
}
