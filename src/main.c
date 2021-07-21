#include "pipex.h"

static int	access_granted(t_pipex *pipex, int type, char *filename_with_path)
{
	if (access(filename_with_path, F_OK) > -1)
	{
		if (type == 1)
		{
			free(pipex->a[0]);
			pipex->a[0] = filename_with_path;
		}
		if (type == 2)
		{
			free(pipex->b[0]);
			pipex->b[0] = filename_with_path;
		}
		return (1);
	}
	return (0);
}

void	path_check(t_pipex *pipex, int type, \
				char **path_arr, char *file_no_path)
{
	char	*filename_with_path;
	char	*filename_with_slash;
	int		i;

	i = -1;
	while (path_arr[++i])
	{
		filename_with_slash = ft_strjoin(path_arr[i], "/");
		if (!filename_with_slash)
			pipex_close(666, pipex);
		filename_with_path = \
			ft_strjoin(filename_with_slash, file_no_path);
		free(filename_with_slash);
		filename_with_slash = NULL;
		if (!filename_with_path)
			pipex_close(666, pipex);
		if (access_granted(pipex, type, filename_with_path) == 1)
			break ;
		free(filename_with_path);
		filename_with_path = NULL;
	}
}

static void	env_path_find(char **envp, t_pipex *pipex)
{
	int		i;
	char	*path_str;

	path_str = NULL;
	i = -1;
	while (envp[++i])
	{
		if ((envp[i][0]) == 'P' && (envp[i][1]) == 'A' && \
		(envp[i][2]) == 'T' && (envp[i][3]) == 'H' && (envp[i][4]) == '=')
		{
			envp[i] += 5;
			pipex->path_ptr = envp[i];
		}
	}
}

void	find_path(t_pipex *pipex, char **envp, int type)
{
	char	*filename_no_path;
	char	**path_arr;

	if ((access(pipex->a[0], F_OK) > -1 && type == 1) || \
		 (access(pipex->b[0], F_OK) > -1 && type == 2))
		return ;
	env_path_find(envp, pipex);
	path_arr = ft_split(pipex->path_ptr, ':');
	if (!path_arr)
		pipex_close(666, pipex);
	if (type == 1)
		filename_no_path = pipex->a[0];
	else
		filename_no_path = pipex->b[0];
	path_check(pipex, type, path_arr, filename_no_path);
	free_arr(path_arr);
}

int	main(int ac, char **av, char **envp)
{
	int		pfd[2];
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	pipex_init(pipex);
	if (ac != 5)
		pipex_close(1, pipex);
	pipex->a = ft_split(av[2], ' ');
	pipex->b = ft_split(av[3], ' ');
	if (!pipex->b || !pipex->a)
		pipex_close(666, pipex);
	find_path(pipex, envp, 1);
	find_path(pipex, envp, 2);
	if (pipe(pfd) < 0)
		pipex_close(5, pipex);
	pipex->pid = fork();
	if (pipex->pid < 0)
		pipex_close(6, pipex);
	if (pipex->pid == 0)
		pipex_child(pipex, pfd, av, envp);
	else
		pipex_parent(pipex, pfd, av, envp);
	close(pfd[0]);
	return (0);
}
