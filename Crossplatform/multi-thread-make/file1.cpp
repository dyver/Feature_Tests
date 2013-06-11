#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void function1()
{
	map<int, string> mis;
	mis[1] = "Virgin";
	for (auto i : mis) cout << i.first << i.second << endl; 
}