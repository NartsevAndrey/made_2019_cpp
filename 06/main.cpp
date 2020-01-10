#include <iostream>
#include "bigint.h"

int main()
{
	BigInt x = 3;
	BigInt y = 1;
	y += 100;
	std::cout << (y) << std::endl;
	return 0;
}
