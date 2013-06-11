#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int getFileSize(const string& path)
{
    ifstream fs(path.c_str(), ios::in | ios::ate);
    return fs.tellg();
}

void read(const string& path)
{
    ifstream fs(path.c_str());
    if (!fs.good()) {
        cout << "Невозможно прочитать файл \"" << path << "\"." << endl;
        return;
    }
    while (fs.good()) {
        string s;
        getline(fs, s);
        cout << "Строка = \"" << s << "\"" << endl;
        stringstream ss(s);
        string parameter;
        ss >> noskipws >> ws;
        getline(ss, parameter, '=');
        size_t found;
        found = parameter.find_last_not_of(" \t");
        if (found != string::npos)
            parameter.erase(found + 1);
        string value;
        ss >> noskipws >> ws;
        getline(ss, value);
        found = value.find_last_not_of(" \t");
        if (found != string::npos)
            value.erase(found + 1);
        cout << "Параметр = \"" << parameter << "\", значение = \"" << value << "\"" << endl;
    }
}

void write(const string& path)
{
    ofstream fs(path.c_str());
    if (!fs.good()) {
        cout << "Невозможно открыть файл \"" << path << "\"." << endl;
        return;
    }
    for (int i = 0; i < 10; ++i) {
        fs << i << endl;
    }
}

int main(void)
{
    const string inPath = "./in.txt";
    const string outPath = "./out.txt";

    cout << "Размер файла = " << getFileSize(inPath) << " байт." << endl;

    read(inPath);
    write(outPath);

    return 0;
}