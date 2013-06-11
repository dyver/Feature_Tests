#include <iostream>

extern void function1();
extern void function2();
extern void function3();
extern void function4();
extern void function5();
extern void function6();
extern void function7();
extern void function8();

using namespace std;

int main()
{
    cout << "Main" << endl;
	function1();
    function2();
    function3();
    function4();
    function5();
    function6();
    function7();
    function8();

	return 0;
}