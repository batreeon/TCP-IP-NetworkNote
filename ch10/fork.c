#include <stdio.h>
#include <unistd.h>

int gval = 10;
int main(int argc, char *argv[])
{
    pid_t pid;
    int lval = 20;
    // 11，25
    gval++, lval += 5;

    pid = fork();
    if (pid == 0)
    // 子进程
        gval += 2, lval += 2;
    else
    // 父进程
        gval -= 2, lval -= 2;

    if (pid == 0)
    // 子进程，13，27
        printf("Child Proc: [%d,%d] \n", gval, lval);
    else
    // 9，23
        printf("Parent Proc: [%d,%d] \n", gval, lval);

    return 0;
}
