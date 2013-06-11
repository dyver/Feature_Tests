#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>

#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    int status;

    if (argc > 1) {
        fd = open("/dev/ttyUSB0", O_RDWR|O_NOCTTY);

        ioctl(fd, TIOCMGET, &status);
        printf("Before: %d\n", status);

        status &= ~TIOCM_DTR;
        status |= TIOCM_RTS;

        ioctl(fd, TIOCMSET, status);

        printf("After: %d\n", status);

        sleep(3);
    } else {
        fd = open("/dev/ttyS0", O_RDWR|O_NOCTTY);
        while (1) {
            ioctl(fd, TIOCMGET, &status);
            printf("Current: %d\n", status);
            sleep(1);
        }
    }

    close(fd);

    return 0;
}