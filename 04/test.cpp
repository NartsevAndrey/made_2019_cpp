#include <iostream>
#include <string>
#include "testing.h"
#include "matrix.h"

const size_t rows = 5;
const size_t cols = 3;

void test_1(void)
{
	Matrix m(rows, cols);
	TEST_CHECK(m.getRows() == 5);
}

void test_2(void)
{
	Matrix m(rows, cols);
	TEST_CHECK(m.getColumns() == 3);
}

void test_3(void)
{
	Matrix m(rows, cols);
	m[1][2] = 5; 
	TEST_CHECK(m[1][2] == 5);
}

void test_4(void)
{
	Matrix m(rows, cols);
	m[1][2] = 5; 
	m *= 3; 
	TEST_CHECK(m[1][2] == 15);
}

void test_5(void)
{
	Matrix m(rows, cols);
	TEST_CHECK(m == m);
}

void test_6(void)
{
	Matrix m(rows, cols);
	Matrix m1(rows - 1, cols);
	TEST_CHECK(m != m1);
}

void test_7(void)
{
	Matrix m(rows, cols);
	m[1][1] = 2;
	m *= 3;
	Matrix m1(rows, cols);
	m1[1][1] = 2;
	TEST_CHECK(m != m1);
}
	
void test_8(void)
{
	Matrix m(rows, cols);
	TEST_EXCEPTION(m[rows][2], std::out_of_range);
}

void test_9(void)
{
	Matrix m(rows, cols);
	TEST_EXCEPTION(m[1][cols], std::out_of_range);
}

void test_10(void)
{
	Matrix m(rows, cols);
	TEST_EXCEPTION(m[-1][2], std::out_of_range);
}

void test_11(void)
{
	Matrix m(rows, cols);
	TEST_EXCEPTION(m[1][-2], std::out_of_range);
}

void test_12(void)
{
	Matrix m(rows, cols);
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            m[i][j] = i + j;
        
	Matrix m1(rows, cols);
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            m1[i][j] = (i + j) * 2;
        
    m *= 2;
	TEST_CHECK(m == m1);
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
   { NULL, NULL }
};


