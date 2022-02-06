#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/wait.h>

int primes[11] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

void prime_sieve(int *data_pipe, int n)
{
    close(data_pipe[1]);
    if (n > 10)
    {
        exit(0);
    }

    int inner_p[2];
    pipe(inner_p);

    if (fork() == 0)
    {
        prime_sieve(inner_p, n + 1);
    }
    else
    {

        close(inner_p[0]);
        int num;
        read(data_pipe[0], &num, 4);
        printf("prime %d\n", num);
        while (read(data_pipe[0], &num, 4) != 0)
        {
            if (num % primes[n] != 0)
            {
                write(inner_p[1], &num, 4);
            }
        }
        close(data_pipe[0]);
        close(inner_p[1]);
        wait(0);
        exit(0);
    }
}

int main()
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        prime_sieve(p, 0);
    }
    else
    {
        close(p[0]);
        int i;
        for (i = 2; i <= 35; i++)
        {
            write(p[1], &i, 4);
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}