#include<unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void    ft_putstr_fd2(char *str1, char *str2)
{
    while(*str1)
        write(2, str1++, 1);
    while(*str2)
        write(2, str2++, 1);
    write(2, "\n", 1);
}

int ft_excute(char *argv[], int comands,int temp, int fd[2], char *env[] )
{
    argv[comands] = NULL;
    dup2(fd[0], temp);
    close(temp);
    execve(argv[0], argv, env);
    ft_putstr_fd2("error: cannot execute ", argv[0]);
    exit (1);
}

int     main(int argc, char **argv, char *env[])
{
    int comandos;
    int temp_fd;
    int fd[2];


    temp_fd = dup(STDIN_FILENO);
    comandos = 0;
    
    while (argv[comandos] && (strcmp(argv[comandos], ";") &&  strcmp(argv[comandos], "|") ))
    {
        comandos ++;
    }
    
    if (strcmp(argv[0], "cd") == 0)
    {
        if(comandos  !=  2)
        {
            ft_putstr_fd2("bash: cd: too many arguments");
        }
        else if (chdir(argv[1]) != 0)
        {
            ft_putstr_fd2("error: cd: cannot change directory to", argv[1]);
        }
    }

    else if (comandos != 0 &&  strcmp(argv[comandos], ";") == 0|| argv[comandos] == NULL)
    {
            if (fork()== 0)
                executer;
            else 
            {
                close(temp_fd);
                while (waitpid(-1, NULL, WUNTRACED) != -1)
                    ;
                temp_fd = dup(STDIN_FILENO);
            }
    }
    else if (comandos != 0 && strcmp(argv[comandos], "|"))
    {
        pipe(fd);
        if(fork == 0)
        {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            execuve
        }
        else
        {
            close(fd[1]);
            close(temp_fd);
            temp_fd = fd[0];
        }


    }
    close(temp_fd);
    return 0;
}

