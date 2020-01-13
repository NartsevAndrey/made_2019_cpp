#include "format.h"
#include "testing.h"

void test_1(void)
{
	TEST_CHECK(format("") == "");
}

void test_2(void)
{
	TEST_CHECK(format("0") == "0");
}

void test_3(void)
{
	TEST_CHECK(format("-1984") == "-1984");
}

void test_4(void)
{
	TEST_CHECK(format("Hello") == "Hello");
}

void test_5(void)
{
	auto text = format("{1}+{1} = \n{0}", 2, "one");
	TEST_CHECK(format(text) == "one+one = \n2");
}

void test_6(void)
{
	auto text = format("{1} + {0} = {2}", 2, 2.0, 4.0f);
	TEST_CHECK(format(text) == "2 + 2 = 4");
}

void test_7(void)
{
	char cs[] = "C string";
	auto text = format("{0}+{1} = {2}", cs, std::string("one"), -3.4);
	TEST_CHECK(format(text) == "C string+one = -3.4");
}

void test_8(void)
{
	auto text = format("{0}+{1} = {2}", 1, true, 2.f);
	TEST_CHECK(format(text) == "1+1 = 2");
}

void test_9(void)
{
	auto text = format("Hello, {0}!", std::string("world"));
	TEST_CHECK(format(text) == "Hello, world!");
}

void test_10(void)
{
	TEST_EXCEPTION(format("{}"), std::exception);
	try
	{
		format("{}");
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: incorrect index");
	}
}

void test_11(void)
{
	TEST_EXCEPTION(format("{"), std::exception);
	try
	{
		format("{");
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: missing close bracket");
	}
}

void test_12(void)
{
	TEST_EXCEPTION(format("}"), std::exception);
	try
	{
		format("}");
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: missing open bracket");
	}
}

void test_13(void)
{
	TEST_EXCEPTION(format("{1}", 3), std::exception);
	try
	{
		format("{1}", 3);
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Extra arguments provided to format");
	}
}

void test_14(void)
{
	auto text = format("{0}, {10}!",
		std::string("0"), 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
	TEST_CHECK(format(text) == "0, 10!");
}

void test_15(void)
{
	TEST_EXCEPTION(format("{-1}"), std::exception);
	try
	{
		format("{-1}");
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: incorrect index");
	}
}

void test_16(void)
{
	TEST_EXCEPTION(format("{1.3}"), std::exception);
	try
	{
		format("{1.3}");
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: incorrect index");
	}
}

void test_17(void)
{
	TEST_EXCEPTION(format("{1f3}"), std::exception);
	try
	{
		format("{1f3}");
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: incorrect index");
	}
}

void test_18(void)
{
	TEST_EXCEPTION(format("{0}+{1 = {2}", 1, true, 2.f), std::exception);
	try
	{
		format("{0}+{1 = {2}", 1, true, 2.f);
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: incorrect index");
	}
}

void test_19(void)
{
	TEST_EXCEPTION(format("{0}+{1} = {2", 1, true, 2.f), std::exception);
	try
	{
		format("{0}+{1} = {2", 1, true, 2.f);
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: missing close bracket");
	}
}

void test_20(void)
{
	TEST_EXCEPTION(format("{0}+{1} = 2}", 1, true, 2.f), std::exception);
	try
	{
		format("{0}+{1} = 2}", 1, true, 2.f);
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: missing open bracket");
	}
}

void test_21(void)
{
	TEST_EXCEPTION(format("{0}+{1 = 2}", 1, true, 2.f), std::exception);
	try
	{
		format("{0}+{1 = 2}", 1, true, 2.f);
	}
	catch (std::exception& e) {
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: incorrect index");
	}
}

void test_22(void)
{
	TEST_EXCEPTION(format("{{0}+{1} = {2}", 1, true, 2.f), std::exception);
	try
	{
		format("{{0}+{1} = {2}", 1, true, 2.f);
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: missing close bracket");
	}
}

void test_23(void)
{
	TEST_EXCEPTION(format("{0}}+{1} = {2}", 1, true, 2.f), std::exception);
	try
	{
		format("{0}}+{1} = {2}", 1, true, 2.f);
	}
	catch (std::exception& e)
	{
		TEST_CHECK(std::string(e.what()) ==
			"Invalid format string: missing open bracket");
	}
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
	{ NULL, NULL }
};
