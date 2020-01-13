#include <stdexcept>
#include <iostream>
#include <string>
#include <new>
#include <vector>
#include <limits>
#include "vector.h"
#include "testing.h"

template <typename T>
bool compare(const Vector<T>& a, const Vector<T>& b)
{
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}

template <typename T>
bool compare_with_std(const Vector<T>& a, const std::vector<T>& b)
{
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}

template <typename T>
bool compare_two_dimention(const Vector<Vector<T>>& a, const Vector<Vector<T>>& b)
{
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); i++)
		if (!compare(a[i], b[i]))
			return false;
	return true;
}

template <typename T>
bool compare_two_dimention_with_std(const Vector<Vector<T>>& a, const std::vector<std::vector<T>>& b)
{
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); i++)
		if (!compare_with_std(a[i], b[i]))
			return false;
	return true;
}

void test_1(void)
{
	Vector<int> a(3, 5);
	std::vector<int> b(3, 5);
	TEST_CHECK(compare_with_std(a, b));
}

void test_2(void)
{
	Vector<std::string> a(3, "Andrew");
	std::vector<std::string> b(3, "Andrew");
	TEST_CHECK(compare_with_std(a, b));
}

void test_3(void)
{
	Vector<int> a(3);
	std::vector<int> b(3);
	TEST_CHECK(compare_with_std(a, b));
}

void test_4(void)
{
	const int n = 5;
	const int m = 10;
	Vector<Vector<int>> a(n, Vector<int>(m, 5));
	std::vector<std::vector<int>> b(n, std::vector<int>(m, 5));

	TEST_CHECK(compare_two_dimention_with_std(a, b));
}

void test_5(void)
{
	Vector<Vector<int>> a = { {1, 2, 3}, {4, 5, 6} };
	std::vector<std::vector<int>> b = { {1, 2, 3}, {4, 5, 6} };

	TEST_CHECK(compare_two_dimention_with_std(a, b));
}

void test_6(void)
{
	Vector<Vector<std::string>> a;
	a.push_back(Vector<std::string>(3, "Andrew"));
	a.push_back(Vector<std::string>(5, "Nartsev"));

	std::vector<std::vector<std::string>> b;
	b.push_back(std::vector<std::string>(3, "Andrew"));
	b.push_back(std::vector<std::string>(5, "Nartsev"));

	TEST_CHECK(compare_two_dimention_with_std(a, b));
}

void test_7(void)
{
	Vector<Vector<std::string>> a;
	a.push_back(Vector<std::string>(3, "Andrew"));
	a.push_back(Vector<std::string>(5, "Nartsev"));
	a.pop_back();

	std::vector<std::vector<std::string>> b;
	b.push_back(std::vector<std::string>(3, "Andrew"));
	b.push_back(std::vector<std::string>(5, "Nartsev"));
	b.pop_back();

	TEST_CHECK(compare_two_dimention_with_std(a, b));
}

void test_8(void)
{
	Vector<int> s = { 2, 2, 2 };
	Vector<Vector<int>> a;
	a.push_back(s);
	TEST_CHECK(compare(s, Vector<int>(3, 2)));
	a.push_back(std::move(s));
	TEST_CHECK(compare(s, Vector<int>()));

	TEST_CHECK(compare_two_dimention(a, Vector<Vector<int>>(2, Vector<int>(3, 2))));
}

void test_9(void)
{
	Vector<int> a(2, 3);
	TEST_EXCEPTION(a[5] = 6, std::runtime_error);
	try
	{
		a[5] = 6;
	}
	catch (std::runtime_error& e)
	{
		TEST_CHECK(std::string(e.what()) == "Vector subscript out of range");
	}
}

void test_10(void)
{
	Vector<int> a(2, 3);
	TEST_EXCEPTION(a[-1] = 6, std::runtime_error);
	try
	{
		a[-1] = 6;
	}
	catch (std::runtime_error& e)
	{
		TEST_CHECK(std::string(e.what()) == "Vector subscript out of range");
	}
}

void test_11(void)
{
	Vector<int> a;
	TEST_EXCEPTION(a.pop_back(), std::runtime_error);
	try
	{
		a.pop_back();
	}
	catch (std::runtime_error& e)
	{
		TEST_CHECK(std::string(e.what()) == "Vector empty before pop_back");
	}
}

void test_12(void)
{
	Vector<int> a;
	TEST_EXCEPTION(a.resize(std::numeric_limits<size_t>::max()), std::runtime_error);
	try
	{
		a.resize(std::numeric_limits<size_t>::max());
	}
	catch (std::runtime_error& e)
	{
		TEST_CHECK(std::string(e.what()) == "Attempt to allocate too much memory");
	}
}

void test_13(void)
{
	Vector<int> a;
	TEST_EXCEPTION(a.reserve(std::numeric_limits<size_t>::max()), std::runtime_error);
	try
	{
		a.reserve(std::numeric_limits<size_t>::max());
	}
	catch (std::runtime_error& e)
	{
		TEST_CHECK(std::string(e.what()) == "Attempt to allocate too much memory");
	}
}

void test_14(void)
{
	Vector<int> a;
	a.resize(100);
	TEST_CHECK(a.size() == 100 && compare(a, Vector<int>(100)));
	a.push_back(10);
	TEST_CHECK(a.size() == 101 && a[100] == 10);
}

void test_15(void)
{
	Vector<int> a(100, 1);
	a.resize(10);
	TEST_CHECK(a.size() == 10 && compare(a, Vector<int>(10, 1)));
	a.push_back(10);
	TEST_CHECK(a.size() == 11 && a[10] == 10);
}

void test_16(void)
{
	Vector<int> a(100, 1);
	a.clear();
	TEST_CHECK(a.empty());
}

void test_17(void)
{
	Vector<int> a = { 1, 2, 3, 4 };
	Vector<int> b = a;

	TEST_CHECK(compare(a, b));
}

void test_18(void)
{
	Vector<int> a = { 5, 5, 5, 5 };
	Vector<int> b = std::move(a);

	TEST_CHECK(a.empty());
	TEST_CHECK(compare(b, Vector<int>(4, 5)));
}

void test_19(void)
{
	Vector<int> a = { 1, 2, 3 };
	a[0] = a[1] = 3;

	TEST_CHECK(compare(a, Vector<int>(3, 3)));
}

void test_20(void)
{
	Vector<Vector<int>> a = { {1, 2, 3}, {4, 5, 6} };
	a.clear();

	TEST_CHECK(a.empty());
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
	{ NULL, NULL }
};
