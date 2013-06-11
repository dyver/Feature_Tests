#include <iostream>
#include <locale>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cwchar>

using namespace std;

std::wstring wide_string(std::string const &s, std::locale const &loc)
{
/*
    wstring ws(s.begin(), s.end());
    return ws;
*/
    if (s.empty())
        return std::wstring();
    std::ctype<wchar_t> const &facet = std::use_facet<std::ctype<wchar_t> >(loc);
    char const *first = s.c_str();
    char const *last = first + s.size();
    std::vector<wchar_t> result(s.size());

    facet.widen(first, last, &result[0]);

    return std::wstring(result.begin(), result.end());
}

std::string narrow_string(std::wstring const &s, std::locale const &loc, char default_char = '?')
{
    if (s.empty())
        return std::string();
    std::ctype<wchar_t> const &facet = std::use_facet<std::ctype<wchar_t> >(loc);
    wchar_t const *first = s.c_str();
    wchar_t const *last = first + s.size();
    std::vector<char> result(s.size());

    facet.narrow(first, last, default_char, &result[0]);

    return std::string(result.begin(), result.end());
}

std::string to_upper(const std::string& source) {
    locale loc("C");
    locale::global(loc);
    wstring ws(wide_string(source, loc));
    cout << source << " ^^^ ";
    wcout << ws << "***" << endl;
    for (auto i : ws) cout << (int)i;
    transform(ws.begin(), ws.end(), ws.begin(), std::towupper);
    wcout << ws << "%%%" << endl;
    return narrow_string(ws, loc);
}

std::string toUpper(const std::string& source)
{
    locale::global(locale("ru_RU.UTF-8"));
    int sourceSize = source.size();
    mbstate_t state = mbstate_t();

    const char* cSource = source.c_str();
    int wideStringBufferSize = mbsrtowcs(NULL, &cSource, 0, &state) + 1;
    vector<wchar_t> wideStringBuffer(wideStringBufferSize);
    mbsrtowcs(&wideStringBuffer[0], &cSource, sourceSize, &state);

    wstring wideString(&wideStringBuffer[0]);
    transform(wideString.begin(), wideString.end(), wideString.begin(), std::towupper);

    const wchar_t* cWstring = wideString.c_str();
    int multiByteStringBufferSize = wcsrtombs(NULL, &cWstring, 0, &state) + 1;
    vector<char> multiByteStringBuffer(multiByteStringBufferSize);
    wcsrtombs(&multiByteStringBuffer[0], &cWstring, multiByteStringBufferSize, &state);

    return string(&multiByteStringBuffer[0]);
}


int main()
{
    string s("Пример");
    cout << s << endl;
    //for (auto i : s) cout << hex << (int)i << "^";
    struct lconv* lcv = localeconv() ;
    std::cout << "toUpper(" << lcv->thousands_sep << ") : " << std::endl ;
    cout << toUpper(s) << endl;
    std::cout << "toUpper(" << lcv->thousands_sep << ") : " << std::endl ;
    //cout << to_upper("Пример") << endl;
    //cout << to_upper("English") << endl;
    /*
    //locale loc("ru_RU.utf8");
    //locale loc("C.UTF-8");
    locale loc("ru_RU.UTF-8");
    //locale::global(loc);
    //setlocale(LC_ALL, "ru_RU.utf8");

    //char site[] = "cplusplus.com";
    char site[] = "По-русски";

    //cout << "The first letter of " << site << " as an uppercase is: ";
    //cout << use_facet< ctype<char> >(loc).toupper(*site);
    //cout << endl;

    cout << "The result of converting " << site << " to uppercase is: ";
    use_facet< ctype<char> >(loc).toupper(site, site + sizeof(site));
    cout << site << endl;
    */

    return 0;
}
