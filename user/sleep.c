#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void Error_Handler()
{
    fprintf(2, "Usage: sleep [time]\n");
    exit(1);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        Error_Handler();
    }
    int time = 0;
    if ((time = atoi(argv[1])) == 0)
    {
        Error_Handler();
    }
    fprintf(1, "Sleep start...\n");
    sleep(time);
    exit(0);
}
