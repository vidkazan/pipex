#include "pipex.h"

void	pipex_init(t_pipex *pipex)
{
	pipex->a = NULL;
	pipex->b = NULL;
	pipex->error_code = 0;
	pipex->path_ptr = NULL;
}

void	free_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

static void	free_pipex(t_pipex *pipex)
{
	if (pipex->a)
		free_arr(pipex->a);
	if (pipex->b)
		free_arr(pipex->b);
	if (pipex)
	{
		free(pipex);
		pipex = NULL;
	}
}

void	pipex_close(int code, t_pipex *pipex)
{
	if (code == 1)
		ft_putstr_fd("pipex: usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
	else if (code == 4)
		ft_putstr_fd("pipex: file2 error: ", 2);
	else if (code == 4)
		ft_putstr_fd(strerror(errno), 2);
	else if (code == 5)
	{
		ft_putstr_fd("pipex: pipe error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
	}
	else if (code == 6)
	{
		ft_putstr_fd("pipex: fork error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
	}
	else if (code == 8)
	{
		ft_putstr_fd("pipex: cmd2 error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
	}
	else if (code == 666)
		ft_putstr_fd("pipex: malloc lucky rare error:)\n", 2);
	free_pipex(pipex);
	exit(1);
}
