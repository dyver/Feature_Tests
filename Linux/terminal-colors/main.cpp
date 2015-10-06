#include <iostream>

namespace TerminalColors {
    const char* Black = "\033[30;40m";
    const char* Red = "\033[31;40m";
    const char* Green = "\033[32;40m";
    const char* Yellow = "\033[33;40m";
    const char* Blue = "\033[34;40m";
    const char* Magenta = "\033[35;40m";
    const char* Cyan = "\033[36;40m";
    const char* White = "\033[37;40m";
    const char* Bold = "\033[1m";
    const char* Underline = "\033[4m";
    const char* Backspace = "\033[1D";
    const char* Default = "\033[0m";
}

using namespace std;
using namespace TerminalColors;

int main() {
    cout << Black << "Чёрный текст" << Default << endl;
    cout << Red << "Красный текст" << Default << endl;
    cout << Green << "Зелёный текст" << Default << endl;
    cout << Yellow << "Жёлтый текст" << Default << endl;
    cout << Blue << "Синий текст" << Default << endl;
    cout << Magenta << "Пурпурный текст" << Default << endl;
    cout << Cyan << "Голубой текст" << Default << endl;
    cout << White << "Белый текст" << Default << endl;
    cout << Bold << "Жирный текст" << Default << endl;
    cout << Underline << "Подчёркнутый текст" << Default << endl;
    cout << "А здесь отутствует последняя буква" << Backspace << " " << Default << endl;

    return 0;
}
