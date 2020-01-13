#include <iostream>
#include <cassert>
#include "format.h"

int main()
{
	try
	{
		auto text = format("{1}+{1} = {0}", 2, "one");
		std::cout << text << std::endl;
		assert(text == "one+one = 2");
	}
	catch (std::runtime_error& error)
	{
		std::cerr << error.what();
	}
	catch (...)
	{
		std::cerr << "Uncnown error" << std::endl;
	}
	return 0;
}
