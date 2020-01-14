#include <iostream>
#include <cassert>
#include "threadpool.h"

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

int main()
{
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, Point(3, 4));
    assert(task1.get() == 25);

    auto task2 = pool.exec([]() { return 1; });
    assert(task2.get() == 1);
    return 0;
}
