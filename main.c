#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

//int main(int ac, char **av, char **envp)
//{
//    int fd[2];
//    pid_t pid;
//
//    pipe(fd);
//    pid = fork();
//    char *a[] = {"/bin/ls","-la","/Volumes/Macintosh HD/Applications", NULL};
//    char *b[] = {"/usr/bin/grep","Xc",NULL};
//    if(pid == 0)
//    {
//        dup2(fd[1], 1);
//        execve(a[0], a, envp);
//        close(fd[0]);
//        close(fd[1]);
//    }
//
//
//    pid_t pid2;
//    pid2 = fork();
//    if(pid2 == 0)
//    {
//        dup2(fd[0], 0);
//        execve(b[0], b, envp);
//        close(fd[0]);
//        close(fd[1]);
//    }
//    close(fd[0]);
//    close(fd[1]);
//
//   waitpid(pid, 0, 0);
//    return 0;
//}

int main(int ac, char **av, char **envp)
{
    int in_fd;
    int out_fd;
    int fd[2];
    pid_t pid;
    char str[1000];
    str[999] = 0;
    in_fd = open("in",O_RDONLY);

    read(in_fd, str, 998);

    pipe(fd);
    pid = fork();
    char *a[] = {"/usr/bin/grep","ffg",NULL};
    char *b[] = {"/usr/bin/grep","1",NULL};
    if(pid == 0)
    {
        dup2(fd[1], 1);
        execve(a[0], a, envp);
        close(fd[0]);
        close(fd[1]);
    }


    pid_t pid2;
    pid2 = fork();
    if(pid2 == 0)
    {
        dup2(fd[0], 0);
        execve(b[0], b, envp);
        close(fd[0]);
        close(fd[1]);
    }
    waitpid(pid, 0, 0);
    return 0;
}