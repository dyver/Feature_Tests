#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

int main()
{
    tm tm1970;
    tm1970.tm_year = 70; // 1970
    tm1970.tm_mon = 0; // january
    tm1970.tm_mday = 1; // 1
    tm1970.tm_hour = 0;
    tm1970.tm_min = 0;
    tm1970.tm_sec = 0;
    time_t secondsOf1970 = ::mktime(&tm1970);
    cout << "secondsOf1970=" << secondsOf1970 << ", ";
    tm tm1999;
    tm1999.tm_year = 99; // 1999
    tm1999.tm_mon = 7; // august
    tm1999.tm_mday = 22; // 22
    tm1999.tm_hour = 0;
    tm1999.tm_min = 0;
    tm1999.tm_sec = 0;
    time_t secondsOf1999 = ::mktime(&tm1999);
    int secondsBetween1970And1980 = int(difftime(secondsOf1999, secondsOf1970));
    cout << "secondsBetween1970And1980=" << secondsBetween1970And1980 << ", " << secondsOf1999 - secondsOf1970;
    cout << endl;
    return 0;
}