#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
    // 构造参数列表
    char **args = (char **)malloc(MAXARG * sizeof(char *));
    int i;
    for (i = 0; i < argc - 1; i++)
    {
        args[i] = malloc(strlen(argv[i + 1]) + 1);
        strcpy(args[i], argv[i + 1]);
    }
    int command_i = i;
    char ch;
    char buf[50];
    i = 0;
    while (read(0, &ch, 1) != 0)
    {
        if (ch == '\n')
        {
            buf[i] = 0;
            args[command_i] = (char *)malloc(strlen(buf) + 1);
            strcpy(args[command_i], buf);
            memset(buf, 0, 50);
            i = 0;
            if (fork() == 0)
            {
                exec(args[0], args);
            }
            else
            {
                wait(0);
                int j;
                for (j = 1; j <= command_i; j++)
                {
                    free(args[j]);
                }
                free(args);
                // 重新构造参数列表
                args = (char **)malloc(MAXARG * sizeof(char *));
                int i;
                for (i = 0; i < argc - 1; i++)
                {
                    args[i] = malloc(strlen(argv[i + 1]) + 1);
                    strcpy(args[i], argv[i + 1]);
                }
                command_i = i;
            }
        }
        else if (ch == ' ')
        {
            buf[i] = 0;
            args[command_i] = (char *)malloc(strlen(buf) + 1);
            strcpy(args[command_i], buf);
            memset(buf, 0, 50);
            command_i++;
            i = 0;
        }
        else
        {
            buf[i++] = ch;
        }
    }
    exit(0);
}