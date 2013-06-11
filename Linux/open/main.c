#include <fcntl.h> /* for open() */
#include <unistd.h> /* for close() */
#include <sys/stat.h> /* for modes (S_*) */

int main(void)
{
    int fd;

    fd = open("./open33.c", O_CREAT|O_RDWR, S_IRWXU|S_IRWXG|S_IRWXO);
    close(fd);

    return 0;
}