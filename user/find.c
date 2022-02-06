#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *name)
{
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512], *p;
    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        if (de.inum == 0)
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if (strcmp(de.name, name) == 0)
        {
            printf("%s\n", buf);
        }
        if (stat(buf, &st) < 0)
        {
            fprintf(3, "find: cannot stat %s\n", buf);
            continue;
        }
        if (st.type == T_DIR && strcmp(".", de.name) != 0 && strcmp("..", de.name) != 0)
        {
            find(buf, name);
        }
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    find(argv[1], argv[2]);
    exit(0);
}