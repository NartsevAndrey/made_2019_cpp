#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "parser.h"

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
            
			Parser parser;
            
            auto callbackBefore = [](const std::string& s) {
                std::cout << "Before\n" << s << std::endl;
                return s;
            };
            parser.setCallbackBefore(callbackBefore);
            
            auto callbackAfter = [](std::vector<std::string>& a) {
                std::cout << "After\n";
                for (std::string& s : a)
                    std::cout << s << std::endl;
            };
            parser.setCallbackAfter(callbackAfter);
            
            auto callbackInt = [](std::string& s) {
                std::cout << "Int: " << stoi(s) << std::endl; 
            };
            auto callbackString = [](std::string& s) {
                std::cout << "String: " << s << std::endl;
            };

            parser.parse(expr, callbackInt, callbackString);
		}
        catch (std::exception& e)
        {
			std::cout << argv[1] << " : exception: " << e.what() << '\n';
			return 1;
		}
	}
	return 0;	
}
