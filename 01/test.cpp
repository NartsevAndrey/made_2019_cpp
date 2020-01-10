#include <iostream>
#include <string>
#include "testing.h"
#include "calc.h"

int test(const std::string& expr) 
{
    Calculator calculator;
	return calculator.calculate(expr);
}

void test_1(void)
{
	TEST_CHECK(test("0") == 0);
}

void test_2(void)
{
	TEST_CHECK(test("69") == 69);
}

void test_3(void)
{
	TEST_CHECK(test("-1") == -1);
}

void test_4(void)
{
	TEST_CHECK(test("1 + 20") == 21);
}

void test_5(void)
{
	TEST_CHECK(test("1 + 20 + 300") == 321);
}

void test_6(void)
{
	TEST_CHECK(test("-1 + 20") == 19);
}

void test_7(void)
{
	TEST_CHECK(test("--1 + 20") == 21);
}
	
void test_8(void)
{
	TEST_CHECK(test("1 + -20") == -19);
}

void test_9(void)
{
	TEST_CHECK(test("-2 * 3") == -6);
}

void test_10(void)
{
	TEST_CHECK(test("2 * -3") == -6);
}

void test_11(void)
{
	TEST_CHECK(test("1 + 10 * 2") == 21);
}

void test_12(void)
{
	TEST_CHECK(test("25 / 5 / 5") == 1);
}

void test_13(void)
{
	TEST_CHECK(test("2 * 3 + 4 * 5") == 26);
}

void test_14(void)
{
	TEST_CHECK(test("5 * 4 + 3 * 2 + 1") == 27);
}

void test_15(void)
{
	TEST_EXCEPTION(test("f45"), std::exception);
	try
    {
		test("f45");
	}
    catch (std::exception& e)
    {
		TEST_CHECK(std::string(e.what()) == "Invalid input");
	}
}

void test_16(void)
{
	TEST_EXCEPTION(test("4 / 0"), std::exception);
	try
    {
		test("4 / 0");
	}
    catch (std::exception& e)
    {
		TEST_CHECK(std::string(e.what()) == "Division by zero");
	}
}

void test_17(void)
{
	TEST_EXCEPTION(test("18 * 19 - 9 / 0"), std::exception);
	try
    {
		test("18 * 19 - 9 / 0");
	}
    catch (std::exception& e)
    {
		TEST_CHECK(std::string(e.what()) == "Division by zero");
	}
}

void test_18(void)
{
	TEST_EXCEPTION(test("1 + - 20 -"), std::exception);
	try
    {
		test("1 + - 20 -");
	}
    catch (std::exception& e)
    {
		TEST_CHECK(std::string(e.what()) == "Invalid input");
	}
}

void test_19(void)
{
	TEST_EXCEPTION(test("1 + 20-"), std::exception);
	try
    {
		test("1 + 20-");
	}
    catch (std::exception& e)
    {
		TEST_CHECK(std::string(e.what()) == "Invalid input");
	}
}

void test_20(void)
{
	TEST_EXCEPTION(test("-"), std::exception);
	try
    {
		test("-");
	}
    catch (std::exception& e)
    {
		TEST_CHECK(std::string(e.what()) == "Invalid input");
	}
}

void test_21(void)
{
	TEST_CHECK(test("-1 - 1") == -2);
}

void test_22(void)
{
	TEST_CHECK(test("-1 - -1") == 0);
}

void test_23(void)
{
	TEST_CHECK(test("2 + 3 * 4 - -2") == 16);
}

void test_24(void)
{
	TEST_CHECK(test("56 - 8 - 12 * 4") == 0);
}

void test_25(void)
{
	TEST_CHECK(test("67 * 2 - 4 * 8 - 12 + 44 - 32 * 4") == 6);
}

void test_26(void)
{
	TEST_CHECK(test("14 - 9 * -1 - 18 * 2 + 44") == 31);
}

TEST_LIST = {
   { "test_1", test_1 },
   { "test_2", test_2 },
   { "test_3", test_3 },
   { "test_4", test_4 },
   { "test_5", test_5 },
   { "test_6", test_6 },
   { "test_7", test_7 },
   { "test_8", test_8 },
   { "test_9", test_9 },
   { "test_10", test_10 },
   { "test_11", test_11 },
   { "test_12", test_12 },
   { "test_13", test_13 },
   { "test_14", test_14 },
   { "test_15", test_15 },
   { "test_16", test_16 },
   { "test_17", test_17 },
   { "test_18", test_18 },
   { "test_19", test_19 },
   { "test_20", test_20 },
   { "test_21", test_21 },
   { "test_22", test_22 },
   { "test_23", test_23 },
   { "test_24", test_24 },
   { "test_25", test_25 },
   { "test_26", test_26 },
   { NULL, NULL }
};


