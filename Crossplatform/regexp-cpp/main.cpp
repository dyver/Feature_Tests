#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

string getItem(const string& text, const string& name) {
    try {
        string s(R"((<)");
        s += name;
        s += R"(>)(.*?)(</)";
        s += name;
        s += R"(>))";
        regex pattern(s);
        smatch matches;
        if (regex_search(text, matches, pattern)) {
            if (matches[2].matched) {
                return matches[2];
            }
        }
    } catch (const regex_error& e) {
        cout << "regex_error caught: " << e.what() << endl;
    }
    return "";
}

string getBookName(const string& text) {
    string bookName;
    string date = getItem(text, "date");
    if (not date.empty()) {
        bookName += date;
        bookName += " ";
    }
    bookName += getItem(text, "book-title");
    bookName += " - ";
    bookName += getItem(text, "first-name");
    bookName += " ";
    bookName += getItem(text, "last-name");
    bookName += ".fb2";
    return bookName;
}

int main() {
    string example(R"("
        "<?xml version=\"1.0\" encoding=\"windows-1251\"?>\n"
        "<description>\n"
            "<title-info>\n"
                "<genre>det_classic</genre>\n"
                "<author>\n"
                    "<first-name>Рекс</first-name>\n"
                    "<last-name>Стаут</last-name>\n"
                "</author>\n"
                "<book-title>Отзвуки убийства</book-title>\n"
                "<date>1941</date>\n"
            "</title-info>\n"
        "</description>\n"
    ")");
    string bookName;
    string content;
    string s;
    while (getline(cin, s)) {
        content += s;
    }
    bookName = getBookName(content);
    cout << bookName << endl;
    return 0;
}
