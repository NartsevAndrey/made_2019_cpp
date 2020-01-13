#include <stdexcept>
#include <iostream>
#include <string>
#include <new>
#include <cassert>
#include "vector.h"


int main()
{
	Vector<std::string> a = { "Narstev", "Andrew" };
	a.push_back("MADE");

	std::string s = "CPP";
	a.push_back(s);

	assert(a.size() == 4);
	assert(a[0] == "Narstev");
	assert(a[1] == "Andrew");
	assert(a[2] == "MADE");
	assert(a[3] == "CPP");

	return 0;
}
