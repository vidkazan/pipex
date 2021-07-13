#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int pfd[2];
    int in;
    int out;
    pid_t pid;

    if(ac != 5)
    {
        printf("pipex: usage: ./pipex file1 cmd1 cmd2 file2\n");
        exit (1);
    }
    pipe(pfd);
    pid = fork();

    char **a = ft_split(av[2], ' ');
    char **b = ft_split(av[3], ' ');
    if(pid == 0)
    {
        close(pfd[0]);
        dup2(pfd[1], 1);
        close(pfd[1]);
        in = open(av[1],O_RDONLY);
        dup2(in, 0);
        execve(a[0], a, envp);
    }
    else
    {
        out = open(av[4], O_RDWR, O_CREAT,O_TRUNC);
        wait(0);
        dup2(pfd[0], 0);
        close(pfd[1]);
        close(pfd[0]);

        dup2(out, 1);
        if (execve(b[0], b, envp) == -1)
            printf("Error");
    }
    return 0;
}