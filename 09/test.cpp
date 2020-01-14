#include <sstream>
#include "threadpool.h"
#include "testing.h"

struct Point
{
    int x;
    int y;
    Point(int a, int b)
        : x(a), y(b)
    {
    }
};

double foo(const Point& p)
{
    return p.x * p.x + p.y * p.y;
}

void test_1(void)
{
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, Point(3, 4));
    TEST_CHECK(task1.get() == 25);

    auto task2 = pool.exec([]() { return 1; });
    TEST_CHECK(task2.get() == 1);
}

void test_2(void)
{
    ThreadPool pool(2);

    auto task1 = pool.exec(foo, Point(3, 4));
    auto task2 = pool.exec(foo, Point(0, 1));
    auto task3 = pool.exec(foo, Point(1, 0));
    auto task4 = pool.exec(foo, Point(-4, -3));

    TEST_CHECK(task1.get() == 25);
    TEST_CHECK(task2.get() == 1);
    TEST_CHECK(task3.get() == 1);
    TEST_CHECK(task4.get() == 25);
}

void test_3(void)
{
    ThreadPool pool(8);
    for (size_t i = 0; i < 100; i++)
    {
        auto task = pool.exec([](size_t i) { return i; }, i);
        TEST_CHECK(task.get() == i);
    }
}

void test_4(void)
{
    ThreadPool pool(8);
    std::vector<std::future<size_t>> tasks;
    for (size_t i = 0; i < 100; i++)
        tasks.emplace_back(pool.exec([](size_t i) { return i; }, i));

	for (size_t i = 0; i < 100; i++)
        TEST_CHECK(tasks[i].get() == i);
}

TEST_LIST = {
   { "test_1", test_1 },
   { "test_2", test_2 },
   { "test_3", test_3 },
   { "test_4", test_4 },
   { NULL, NULL }
};
