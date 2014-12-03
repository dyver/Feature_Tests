#include <iostream>

using namespace std;

int main(void)
{
    const char* black = "\033[30;40m";
    const char* red = "\033[31;40m";
    const char* green = "\033[32;40m";
    const char* yellow = "\033[33;40m";
    const char* blue = "\033[34;40m";
    const char* magenta = "\033[35;40m";
    const char* cyan = "\033[36;40m";
    const char* white = "\033[37;40m";

    cout << black << "Чёрный текст" << endl;
    cout << red << "Красный текст" << endl;
    cout << green << "Зелёный текст" << endl;
    cout << yellow << "Жёлтый текст" << endl;
    cout << blue << "Синий текст" << endl;
    cout << magenta << "Пурпурный текст" << endl;
    cout << cyan << "Голубой текст" << endl;
    cout << white << "Белый текст" << endl;

    return 0;
}
