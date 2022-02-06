#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main()
{
    int p[2];
    pipe(p);

    if (fork() == 0)
    {
        close(p[1]);
        char buf[5];
        read(p[0], buf, 4);
        fprintf(1, "%d: received ping\n", getpid());
        close(p[0]);
        exit(0);
    }
    else
    {
        close(p[0]);
        write(p[1], "test", 4);
        close(p[1]);
        wait(0);
        fprintf(2, "%d: received pong\n", getpid());
        exit(0);
    }
}