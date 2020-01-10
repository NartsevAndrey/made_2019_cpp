#include <string>
#include "testing.h"
#include "allocator.h"

char testCharGood(int n) 
{
    LinearAllocator allocator(n);
    char* a = allocator.alloc(n);
    for (int i = 0; i < n; i++)
    {
        a[i] = 'a' + i;
    }
    return a[n - 1];
}

char* testCharBad(int n) 
{
    LinearAllocator allocator(n);
    char* a = allocator.alloc(n + 1);
    return a;
}

int testIntGood(int n) 
{
    LinearAllocator allocator(n * sizeof(int));
    int* a = reinterpret_cast<int*>(allocator.alloc(n * sizeof(int)));
    for (int i = 0; i < n; i++)
    {
        a[i] = i + 1;
    }
    return a[n - 1];
}

char testCharWithReset(int n) 
{
    LinearAllocator allocator(n);
    char* a = allocator.alloc(n);
    for (int i = 0; i < n; i++)
    {
        a[i] = 'a' + i;
    }
    allocator.reset();
    char* b = allocator.alloc(n);
    for (int i = 0; i < n; i++)
    {
        b[i] = 'a' + n - 1 - i;
    }
    return b[n - 1];
}

int* testIntBad(int n) 
{
    LinearAllocator allocator(n * sizeof(int));
    int* a = reinterpret_cast<int*>(allocator.alloc((n + 1) * sizeof(int)));
    return a;
}

int test(int n)
{
    LinearAllocator allocator(n * sizeof(int));
    for (int i = 0; i <= n; i++)
    {
        int* x = reinterpret_cast<int*>(allocator.alloc(sizeof(int)));
        if (x == nullptr)
        {
            return i;
        }
    }
    return -1;
}

void test_1(void)
{
	TEST_CHECK(testCharGood(1) == 'a');
}

void test_2(void)
{
	TEST_CHECK(testCharGood(2) == 'b');
}

void test_3(void)
{
	TEST_CHECK(testCharGood(5) == 'e');
}

void test_4(void)
{
	TEST_CHECK(testCharGood(26) == 'z');
}

void test_5(void)
{
	TEST_CHECK(testCharBad(5) == nullptr);
}

void test_6(void)
{
	TEST_CHECK(testIntGood(1) == 1);
}

void test_7(void)
{
	TEST_CHECK(testIntGood(5) == 5);
}

void test_8(void)
{
	TEST_CHECK(testIntBad(5) == nullptr);
}

void test_9(void)
{
	TEST_EXCEPTION(testCharGood(0), std::exception);
	try
    {
		testCharGood(0);
	}
    catch (std::exception& e)
    {
		TEST_CHECK(std::string(e.what()) ==
            "Attempt to select a zero-size block");
	}
}

void test_10(void)
{
	TEST_EXCEPTION(testIntGood(0), std::exception);
	try
    {
		testIntGood(0);
	}
    catch (std::exception& e)
    {
		TEST_CHECK(std::string(e.what()) ==
            "Attempt to select a zero-size block");
	}
}

void test_11(void)
{
	TEST_EXCEPTION(test(0), std::exception);
	try
    {
		test(0);
	}
    catch (std::exception& e)
    {
		TEST_CHECK(std::string(e.what()) ==
            "Attempt to select a zero-size block");
	}
}

void test_12(void)
{
	TEST_CHECK(testCharWithReset(5) == 'a');
}

void test_13(void)
{
	TEST_CHECK(test(1) == 1);
}

void test_14(void)
{
	TEST_CHECK(test(1024) == 1024);
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
   { NULL, NULL }
};


