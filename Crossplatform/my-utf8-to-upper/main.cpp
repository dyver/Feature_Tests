#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

vector<uint16_t> upperLetters = {
    'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ё', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н',
    'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я'
};

vector<uint16_t> lowerLetters = {
    'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н',
    'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я'
};

uint8_t lowByte(uint16_t w) {
    return w bitand 0x00ff;
}

uint8_t highByte(uint16_t w) {
    return (w >> 8) bitand 0x00ff;
}

uint16_t makeSymbol(uint8_t high, uint8_t low) {
    return (static_cast<uint16_t>(high) << 8) bitor low;
}

std::string toUpper(const std::string& source) {
    string result;
    for (auto i = 0U; i < source.size(); ++i) {
        if (source[i] bitand 0x80) {
            if (i == source.size() - 1) {
                return result;
            }
            uint16_t symbol = makeSymbol(source[i], source[i + 1]);
            bool lowFound = false;
            for (auto j = 0U; j < lowerLetters.size(); ++j) {
                if (lowerLetters[j] == symbol) {
                    result += highByte(upperLetters[j]);
                    result += lowByte(upperLetters[j]);
                    lowFound = true;
                    break;
                }
            }
            if (!lowFound) {
                bool invalidSymbol = true;
                for (auto j = 0U; j < upperLetters.size(); ++j) {
                    if (upperLetters[j] == symbol) {
                        result += source[i];
                        result += source[i + 1];
                        invalidSymbol = false;
                        break;
                    }
                }
                if (invalidSymbol) {
                    return result;
                }
            }
            ++i;
        } else {
            result += toupper(source[i]);
        }
    }
    return result;
}


int main() {
    string s("Пример +=-_() and English");
    cout << "Original: ^" << s << "^" << endl;
    cout << "In upper case: ^" << toUpper(s) << "^" << endl;

    return 0;
}
