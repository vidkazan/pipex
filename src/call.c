#include "pipex.h"

void	pipex_child(t_pipex *pipex, int pfd[], char **av, char **envp)
{
	int	in;

	in = open(av[1], O_RDONLY);
	if (in < 0)
	{
		ft_putstr_fd("pipex: file1 error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	dup2(in, 0);
	dup2(pfd[1], 1);
	if (execve(pipex->a[0], pipex->a, envp) < 0)
	{
		ft_putstr_fd("pipex: cmd1 error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
}

void	pipex_parent(t_pipex *pipex, int pfd[], char **av, char **envp)
{
	int	out;

	wait(0);
	close(pfd[1]);
	out = open(av[4], O_RDWR, O_CREAT, O_TRUNC);
	if (out < 0)
		pipex_close(4, pipex);
	dup2(out, 1);
	dup2(pfd[0], 0);
	if (execve(pipex->b[0], pipex->b, envp) < 0)
		pipex_close(8, pipex);
}
