#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>

using namespace std;

const char* ctrl_default = "\033[0m";
const char* ctrl_black = "\033[30;40m";
const char* ctrl_red = "\033[31;40m";
const char* ctrl_green = "\033[32;40m";
const char* ctrl_yellow = "\033[33;40m";
const char* ctrl_blue = "\033[34;40m";
const char* ctrl_magenta = "\033[35;40m";
const char* ctrl_cyan = "\033[36;40m";
const char* ctrl_white = "\033[37;40m";
const char* ctrl_bold = "\033[1m";
const char* ctrl_halftone = "\033[2m";
const char* ctrl_underline = "\033[4m";
const char* ctrl_flash = "\033[5m";
const char* ctrl_backspace = "\033[1D";

bool isActive = false;

int openSerial(const string& deviceName) {
    int fd = open(deviceName.c_str(), O_RDWR | O_NOCTTY);
    return fd;
}

bool setParameters(int fd) {
    // установить скорость и параметры порта
    termios ts;
    tcgetattr(fd, &ts);
    ts.c_cc[VMIN] = 1;
    ts.c_cc[VTIME] = 0;
    ts.c_oflag = 0;
    ts.c_lflag = 0;
    ts.c_iflag = 0;
    ts.c_lflag &= ~ICANON;
    speed_t speed = B115200;
    if (cfsetospeed(&ts, speed) == -1) {
        cout << "Ошибка! Не могу установить выходную скорость" << endl;
        return false;
    }
    if (cfsetispeed(&ts, speed) == -1) {
        cout << "Ошибка! Не могу установить входную скорость" << endl;
        return false;
    }
    ts.c_cflag &= ~CSIZE;
    ts.c_cflag |= CS8 | CREAD;
    ts.c_cflag &= ~PARENB;
    ts.c_cflag &= ~CSTOPB;
    // установить блокирующий режим функции read()
    if (fcntl(fd, F_SETFL, 0) < 0) {
        cout << "Ошибка! Не могу установить блокирующий режим" << endl;
        return false;
    }
    // установить режимы управления портом
    if (tcsetattr(fd, TCSANOW, &ts) == -1) {
        cout << "Ошибка! Не могу установить режимы устройства" << endl;
        return false;
    }
    return true;
}

int getStatus(int fd) {
    int status;
    int ioResult = ioctl(fd, TIOCMGET, &status);
    if (ioResult == -1) {
        return -1;
    }
    return status;
}

void printStatus(int status) {
    cout << "Flags: ";
    if (status bitand TIOCM_DTR) {
        cout << "DTR ";
    }
    if (status bitand TIOCM_RTS) {
        cout << "RTS ";
    }
    if (status bitand TIOCM_CTS) {
        cout << "CTS ";
    }
    if (status bitand TIOCM_CAR) {
        cout << "CAR ";
    }
    if (status bitand TIOCM_RI) {
        cout << "RI ";
    }
    if (status bitand TIOCM_DSR) {
        cout << "DSR ";
    }
    cout << endl;
}

vector<string> serials;

void validateSerial(const string& deviceName) {
    int fd = openSerial(deviceName);
    if (fd == -1) {
        return;
    }
    int status = getStatus(fd);
    if (status == -1) {
        close(fd);
        return;
    }
    close(fd);
    serials.push_back(deviceName);
    cout << "#" << serials.size() << ". " << deviceName << endl;
    //printStatus(status);
    return;
}

void listSerial() {
    cout << "List of active serial ports:" << endl;
    for (int i = 0; i < 32; ++i) {
        validateSerial("/dev/ttyS" + to_string(i));
    }
    for (int i = 0; i < 32; ++i) {
        validateSerial("/dev/ttymxc" + to_string(i));
    }
    for (int i = 0; i < 32; ++i) {
        validateSerial("/dev/ttyUSB" + to_string(i));
    }
}

string chooseSerial(int choosed = -1) {
    if (choosed == -1) {
        cout << "Input number of serial port: ";
        cin >> choosed;
    }
    if (choosed > 0 and choosed <= (int)serials.size()) {
        return serials[choosed - 1];
    }
    return "";
}

int inSize = 20;
int outSize = 20;
int PacketCounterFieldSize = 8;
int endMarkerPosition = 19;
vector<char> inBuf(inSize);
vector<char> outBuf(outSize);

const char beginMarker = '#';
const char endMarker = '*';
vector<char> sample = { beginMarker, 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', endMarker };

int packetCounter = 0;

int ErrorsCounterFieldSize = 7;
int noAskErrorsCounter = 0;
int noReplyErrorsCounter = 0;
int malformedAskErrorsCounter = 0;
int malformedReplyErrorsCounter = 0;

void printInfo() {
    string message = "PC:";
    {
        stringstream ss;
        ss << setw(PacketCounterFieldSize) << setfill('_') << packetCounter;
        message += ss.str();
    }

    if (isActive) {
        {
            message += " NR:";
            stringstream ss;
            ss << setw(ErrorsCounterFieldSize) << setfill('_') << noReplyErrorsCounter;
            message += ss.str();
        }
        {
            message += " MR:";
            stringstream ss;
            ss << setw(ErrorsCounterFieldSize) << setfill('_') << malformedReplyErrorsCounter;
            message += ss.str();
        }
    } else {
        {
            message += " NA:";
            stringstream ss;
            ss << setw(ErrorsCounterFieldSize) << setfill('_') << noAskErrorsCounter;
            message += ss.str();
        }
        {
            message += " MA:";
            stringstream ss;
            ss << setw(ErrorsCounterFieldSize) << setfill('_') << malformedAskErrorsCounter;
            message += ss.str();
        }
    }

    cout << "\033[" + to_string(message.size()) + "D" << flush;
    cout << message;
}

void fillBuf() {
    copy(begin(sample), end(sample), begin(outBuf));
    stringstream ss;
    ss << setw(PacketCounterFieldSize) << setfill('0') << packetCounter;
    string sss = ss.str();
    copy(begin(sss), end(sss), begin(outBuf) + 1);
    fill(begin(inBuf), end(inBuf), '$');
}

int inBufPos = 0;

bool checkPacket() {
    string packetField;
    copy(begin(inBuf) + 1, begin(inBuf) + 1 + PacketCounterFieldSize, back_inserter(packetField));
    int receivedPacketCounter = stoi(packetField);
    if (receivedPacketCounter != packetCounter) {
        packetCounter = receivedPacketCounter;
        return false;
    }
    vector<char> buf;
    copy(begin(sample), end(sample), back_inserter(buf));
    stringstream ss;
    ss << setw(PacketCounterFieldSize) << setfill('0') << packetCounter;
    string sss = ss.str();
    copy(begin(sss), end(sss), begin(buf) + 1);
    if (equal(begin(buf), end(buf), begin(inBuf))) {
        return true;
    }
    return false;
}

bool checkAsk() {
    return checkPacket();
}

bool checkReply() {
    return checkPacket();
}

bool writeToSerial(int fd) {
    size_t result = write(fd, outBuf.data(), outBuf.size());
    if (result != outBuf.size()) {
        return false;
    }
    return true;
}

bool waitForReady(int fd) {
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    fd_set rfds = fds;
    int PortReadTimeoutInMicroseconds = 1000000;
    timeval timeout = { 0, PortReadTimeoutInMicroseconds };
    int res = select(fd + 1, &rfds, NULL, NULL, &timeout);
    if (res <= 0) {
        return false;
    }
    return true;
}

void printInBuf() {
    cout << endl;
    for (auto i : inBuf) {
        if (isprint(i)) {
            cout << i;
        } else {
            cout << ctrl_yellow << to_string(i) << ctrl_default;
        }
    }
    cout << endl;
}

bool readFromSerial(int fd) {
    vector<char> buf(100);
    //size_t result = fread(buf.data(), 1, buf.size(), )
    int result = read(fd, buf.data(), buf.size());
    if (result == 0) {
        return false;
    }
    if (result > (int)inBuf.size()) {
        inBufPos = 0;
        fillBuf();
//        printInBuf();
        return false;
    }
    auto pos = find(begin(buf), begin(buf) + result, '#');
    if (pos != begin(buf) + result) {
        fillBuf();
        copy(pos, begin(buf) + result, begin(inBuf));
        inBufPos = result;
    } else {
        size_t toAppend = result;
        if (toAppend > inBuf.size() - inBufPos) {
            toAppend = inBuf.size() - inBufPos;
        }
        copy(begin(buf), begin(buf) + toAppend, begin(inBuf) + inBufPos);
        inBufPos += toAppend;
    }
    if (inBuf[endMarkerPosition] == '*' and inBufPos == endMarkerPosition + 1) {
//        printInBuf();
        inBufPos = 0;
        return true;
    }
//    printInBuf();
    return false;
}

void sendAsk(int fd) {
    writeToSerial(fd);
}

void sendReply(int fd) {
    writeToSerial(fd);
}

bool receiveAsk(int fd) {
    for (int i = 0; i < 100; ++i) {
        if (not waitForReady(fd)) {
            return false;
        }
        if (readFromSerial(fd)) {
            return true;
        }
    }
    return false;
}

bool receiveReply(int fd) {
    return receiveAsk(fd);
}

int main(int argc, char** argv) {
    isActive = false;
    int portNumber = -1;
    if (argc > 1) {
        if (argv[1][0] == 'a') {
            isActive = true;
            if (argc > 2) {
                portNumber = atoi(argv[2]);
            }
        } else {
            portNumber = atoi(argv[1]);
        }
    } else {
    }
    listSerial();
    if (serials.empty()) {
        cout << "No serial ports found!" << endl;
        return 1;
    }
    string choosed = chooseSerial(portNumber);
    if (choosed == "") {
        cout << "No such port!" << endl;
        return 1;
    }
    cout << endl << "Selected " << choosed << " port" << endl;
    cout << " Working in ";
    if (isActive) {
        cout << "active";
    } else {
        cout << "passive";
    }
    cout << " mode" << endl;
    cout << "Legend:" << endl;
    cout << " PC - packet counter" << endl;
    if (isActive) {
        cout << " NR - no reply counter" << endl;
        cout << " MR - malformed packets counter" << endl;
    } else {
        cout << " NA - no ask counter" << endl;
        cout << " MA - malformed ask counter" << endl;
    }
    int fd = openSerial(choosed);
    if (fd == -1) {
        cout << "ERROR in opening existing port!!!" << endl;
        return 2;
    }
    if (not setParameters(fd)) {
        cout << "ERROR setting parameters!!!" << endl;
        close(fd);
        return 2;
    }
    if (isActive) {
        while (true) {
            printInfo();
            this_thread::sleep_for(chrono::milliseconds(10));
            fillBuf();
            sendAsk(fd);
            //this_thread::sleep_for(chrono::milliseconds(20));
            if (not receiveReply(fd)) {
                ++noReplyErrorsCounter;
                continue;
            }
            if (not checkReply()) {
                ++malformedReplyErrorsCounter;
                continue;
            }
            ++packetCounter;
        }
    } else  {
        while (true) {
            printInfo();
            if (not receiveAsk(fd)) {
                ++noAskErrorsCounter;
                continue;
            }
            if (not checkAsk()) {
                ++malformedAskErrorsCounter;
                continue;
            }
            fillBuf();
            sendReply(fd);
            ++packetCounter;
        }
    }
    close(fd);
    return 0;
}
