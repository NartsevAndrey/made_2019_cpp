#include <iostream>
#include <string>
#include <vector>
#include "testing.h"
#include "parser.h"


using Callback = void(*)(std::string& s);

using CallbackBefore = std::string(*)(const std::string& s);

using CallbackAfter = void(*)(std::vector<std::string>& a);

std::vector<std::string> test(const std::string& expr,
    CallbackBefore before, CallbackAfter after, Callback forInt, Callback forString) 
{
    Parser parser(before, after, forInt, forString);
	return parser.parse(expr);
}

std::vector<std::string> testSetters(const std::string& expr,
    CallbackBefore before, CallbackAfter after, Callback forInt, Callback forString)
{
    Parser parser;
    parser.setCallbackBefore(before);
    parser.setCallbackAfter(after);
    parser.setCallbackInt(forInt);
    parser.setCallbackString(forString);

	return parser.parse(expr);
}

void test_1(void)
{
    std::string s = "Andrey     Nartsev 21  ";    
	TEST_CHECK(test(s, nullptr, nullptr, nullptr, nullptr) ==
        std::vector<std::string>({"Andrey", "Nartsev", "21"}));
}

void test_2(void)
{
    std::string s = "Andrey     Nartsev 21";    
	TEST_CHECK(testSetters(s, nullptr, nullptr, nullptr, nullptr) ==
        std::vector<std::string>({"Andrey", "Nartsev", "21"}));
}

void test_3(void)
{
	std::string s = "Andrey     Nartsev 21  ";   
    auto callbackBefore = [](const std::string& s) {
        return "MADE " + s + " MADE";
    };
	TEST_CHECK(test(s, callbackBefore, nullptr, nullptr, nullptr) ==
        std::vector<std::string>({"MADE", "Andrey", "Nartsev", "21", "MADE"}));
}

void test_4(void)
{
	std::string s = "Andrey     Nartsev 21  ";   
    auto callbackAfter = [](std::vector<std::string>& a) {
        a.push_back("Good job!");
    };
	TEST_CHECK(test(s, nullptr, callbackAfter, nullptr, nullptr) ==
        std::vector<std::string>({"Andrey", "Nartsev", "21", "Good job!"}));
}

void test_5(void)
{
    std::string s = "Andrey     Nartsev 21  ";   
    auto callbackString = [](std::string& a) {
        a += "!";
    };
	TEST_CHECK(test(s, nullptr, nullptr, nullptr, callbackString) ==
        std::vector<std::string>({"Andrey!", "Nartsev!", "21"}));
}

void test_6(void)
{
	std::string s = "Andrey     Nartsev 21  ";   
    auto callbackInt = [](std::string& s) {
        s = std::to_string(stoi(s) * 2);
    };
	TEST_CHECK(test(s, nullptr, nullptr, callbackInt, nullptr) ==
        std::vector<std::string>({"Andrey", "Nartsev", "42"}));
}

void test_7(void)
{
	std::string s = "Andrey     Nartsev 21  ";
    auto callbackBefore = [](const std::string& s) {
        return "MADE " + s + " MADE";
    };
    auto callbackAfter = [](std::vector<std::string>& a) {
        a.push_back("Good job!");
    };
    auto callbackInt = [](std::string& s) {
        s = std::to_string(stoi(s) * 2);
    };
    auto callbackString = [](std::string& a) {
        a += "!";
    };
	TEST_CHECK(test(s, callbackBefore, callbackAfter, callbackInt, callbackString) ==
        std::vector<std::string>({"MADE!", "Andrey!", "Nartsev!", "42", "MADE!", "Good job!"}));    
}

TEST_LIST = {
   { "test_1", test_1 },
   { "test_2", test_2 },
   { "test_3", test_3 },
   { "test_4", test_4 },
   { "test_5", test_5 },
   { "test_6", test_6 },
   { "test_7", test_7 },
   { NULL, NULL }
};


