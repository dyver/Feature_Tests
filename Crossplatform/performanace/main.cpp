#include <iostream>
#include <string>
using namespace std;

#include <time.h>

#include "SUtils.h"

const long int cycles = 1L << 26;

time_t before = 0;
time_t after = 0;

void tested_function()
{
	d1cout << "1" << flush;
	d2cout << "2" << flush;
	d3cout << "3" << flush;
}

void begin()
{
	before = time(NULL);
	cout << "Before: " << before << endl;
	unsigned int rrr;
	rrr = -1;
	cout << rrr << endl;
}

void process()
{
	cout << "Performing " << cycles << " cycles" << endl;
	for (long int i = 0L; i < cycles; ++i)
		tested_function();
}

void end()
{
	after = time(NULL);
	cout << "After: " << after << endl;
}

void result()
{
	long int difference = after - before;
	cout << "Difference: " << difference << endl;
}

int main(int argc, char *argv[])
{
	begin();
	process();
	end();
	result();
//	cout << "Press any key to continue..." << endl;
//	cin.get();
	return 0;
}