#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>

using namespace std;

int main() {
    for (int i = 0; i < 32; ++i) {
        string deviceName = "/dev/ttyS" + to_string(i);
        int fd = open(deviceName.c_str(), O_RDWR | O_NOCTTY);
        if (fd == -1) {
            continue;
        }
        int status;
        ioctl(fd, TIOCMGET, &status);
        cout << "Status=" << status << endl;
        vector<char> buf(10);
        int result = write(fd, buf.data(), buf.size());
        cout << "Read=" << result << endl;
        cout << "Found active " << deviceName << " serial port" << endl;
        close(fd);
    }
    return 0;
}
