#include <iostream>
#include <cassert>
#include "matrix.h"

int main()
{
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);

    m[1][2] = 5;
    double x = m[4][1];

    m *= 3;

    Matrix m1(rows, cols);

    assert(m != m1);

    return 0;
}