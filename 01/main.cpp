#include <iostream>
#include <string>
#include <stdexcept>
#include "calc.h"

int main(int argc, char *argv[])
{
	if (argc > 1)
    {
		try
        {
			std::string expr;
			for (int i = 1; i < argc; i++)
            {
				expr += argv[i];
            }
            
			Calculator calculator;
            std::cout << calculator.calculate(expr) << std::endl;
		}
        catch (std::exception& e)
        {
			std::cout << argv[1] << " : exception: " << e.what() << '\n';
			return 1;
		}
	}
	return 0;	
}
