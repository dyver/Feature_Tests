#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

vector<string> lines;

void read(const string& path)
{
    ifstream fs(path.c_str());
    if (!fs.good()) {
        cout << "Невозможно прочитать файл \"" << path << "\"." << endl;
        return;
    }
    lines.clear();
    while (fs.good()) {
        string s;
        getline(fs, s);
        lines.push_back(s);
    }
}

void write(const string& path)
{
    ofstream fs(path.c_str());
    if (!fs.good()) {
        cout << "Невозможно открыть файл \"" << path << "\"." << endl;
        return;
    }
    for (vector<string>::size_type i = 0; i < lines.size(); ++i) {
        fs << lines[i] << endl;
    }
}

int main(void)
{
    const string inPath = "./in.txt";
    const string outPath = "./out.txt";

    read(inPath);
    sort(lines.begin(), lines.end());
    write(outPath);

    return 0;
}