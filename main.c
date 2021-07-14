#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int pfd[2];
    int in;
    int out;
    pid_t pid;
    //int stdout = dup(1);
    if(ac != 5)
    {
        printf("pipex: usage: ./pipex file1 cmd1 cmd2 file2\n");
        exit (1);
    }
    char **a = ft_split(av[2], ' ');
    char **b = ft_split(av[3], ' ');

    pipe(pfd);
    pid = fork();

    if(pid == 0)
    {
        in = open(av[1],O_RDONLY);
        dup2(in, 0);
        dup2(pfd[1],1);
        execve(a[0],a, envp);
    }
//    else
//    {
        wait(0);
        close(pfd[1]);
//        waitpid(pid, 0, 0);
        out = open(av[4], O_RDWR, O_CREAT, O_TRUNC);
        dup2(out, 1);
        dup2(pfd[0], 0);
        execve(b[0], b, envp);
//    }
//    return 0;
}