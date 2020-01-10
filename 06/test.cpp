#include "bigint.h"
#include "testing.h"

void test_1(void)
{
	TEST_CHECK(BigInt(1) == BigInt(1));
}

void test_2(void)
{
	TEST_CHECK(BigInt(-1) == BigInt(-1));
}

void test_3(void)
{
	unsigned int n = 100000;
	TEST_CHECK(BigInt(n) == BigInt(100000));
}

void test_4(void)
{
	size_t n = 1000000000000000;
	TEST_CHECK(BigInt(n) == BigInt(1000000000000000UL));
}

void test_5(void)
{
	TEST_CHECK(BigInt(-1) != BigInt(1));
}

void test_6(void)
{
	TEST_CHECK(BigInt(100000) != BigInt(100));
}

void test_7(void)
{
	TEST_CHECK(BigInt(10) < BigInt(100));
}

void test_8(void)
{
	TEST_CHECK(BigInt(100) > BigInt(10));
}

void test_9(void)
{
	TEST_CHECK(BigInt(-10) < BigInt(10));
}

void test_10(void)
{
	TEST_CHECK(BigInt(10) > BigInt(-100));
}

void test_11(void)
{
	TEST_CHECK(BigInt(-11) < BigInt(-10));
}

void test_12(void)
{
	TEST_CHECK(BigInt(10) < BigInt(11));
}

void test_13(void)
{
	TEST_CHECK(BigInt(10) <= BigInt(10));
}

void test_14(void)
{
	TEST_CHECK(BigInt(11) >= BigInt(10));
}

void test_15(void)
{
	TEST_CHECK(BigInt(11) > BigInt(10));
}


void test_16(void)
{
	TEST_CHECK(BigInt(11) >= BigInt(11));
}

void test_17(void)
{
	TEST_CHECK(BigInt(11) == 11);
}

void test_18(void)
{
	TEST_CHECK(11 == BigInt(11));
}

void test_19(void)
{
	TEST_CHECK(666 != BigInt(665));
}

void test_20(void)
{
	TEST_CHECK(BigInt(665) != 666);
}

void test_21(void)
{
	TEST_CHECK(BigInt(10) < 11);
}

void test_22(void)
{
	TEST_CHECK(BigInt(-10) > -11);
}

void test_23(void)
{
	TEST_CHECK(BigInt(-11) >= -11);
}
		   
void test_24(void)
{
	BigInt x = 10;
	TEST_CHECK(x + x + x == BigInt(30));
}

void test_25(void)
{
	BigInt x = 10;
	TEST_CHECK(x - x - x == BigInt(-10));
}

void test_26(void)
{
	BigInt x = 10;
	TEST_CHECK(x + -x == BigInt(0));
}

void test_27(void)
{
	BigInt x = 10;
	TEST_CHECK(-x + x == BigInt(0));
}

void test_28(void)
{
	BigInt x = 10;
	TEST_CHECK(-x + -x == BigInt(-20));
}

void test_29(void)
{
	BigInt x = 10;
	TEST_CHECK(-x - -x == BigInt(0));
}

void test_30(void)
{
	BigInt x = 10;
	TEST_CHECK(-x - x == BigInt(-20));
}

void test_31(void)
{
	BigInt x = 1;
	BigInt y = 99;
	TEST_CHECK(x + y == BigInt(100));
}

void test_32(void)
{
	BigInt x = 100;
	BigInt y = 1;
	TEST_CHECK(x - y == BigInt(99));
}

void test_33(void)
{
	BigInt x = 100000;
	BigInt y = 1;
	TEST_CHECK(x - y == BigInt(99999));
}

void test_34(void)
{
	BigInt x = 100000000000000;
	for (int i = 0; i < 100; i++)
		x += x;
	TEST_CHECK(x == x);
}

void test_35(void)
{
	BigInt x = 600;
	BigInt y = 66;
	x += y;
	TEST_CHECK(x == 666);
}		   
			   
void test_36(void)
{
	BigInt x = 700;
	BigInt y = 34;
	x -= y;
	TEST_CHECK(x == 666);
}
			   		   
void test_37(void)
{
	BigInt x = 700;
	BigInt y = 34;
	TEST_CHECK(-32 + x + -y - 20 == 614);
}
			   
void test_38(void)
{
	BigInt a = 1;
	BigInt b = a;
	BigInt c = a + b + 2;
	TEST_CHECK(c == 4);
}

void test_39(void)
{
    const int n = 10;
    char* s = new char[n];
    s[0] = '1';
    for (size_t i = 1; i < n; i++) 
        s[i] = '0';
	BigInt a(s, n);
	TEST_CHECK(a == 1000000000UL);
}
	
void test_40(void)
{
	TEST_CHECK(BigInt("123", 3) == 123);
}
        
void test_41(void)
{
	TEST_CHECK(BigInt("0", 1) == 0);
}

void test_42(void)
{
	TEST_CHECK(BigInt("-11", 3) == -11);
}

void test_43(void)
{
	BigInt a("-25", 3);
	BigInt b(-25);
	BigInt c(0UL);
	TEST_CHECK(a - b + c == BigInt("0", 1));
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
   { "test_27", test_27 },
   { "test_28", test_28 },
   { "test_29", test_29 },
   { "test_30", test_30 },
   { "test_31", test_31 },
   { "test_32", test_32 },
   { "test_33", test_33 },
   { "test_34", test_34 },
   { "test_35", test_35 },
   { "test_36", test_36 },
   { "test_37", test_37 },
   { "test_38", test_38 },
   { "test_39", test_39 },
   { "test_40", test_40 },
   { "test_41", test_41 },
   { "test_42", test_42 },
   { "test_43", test_43 },
   { NULL, NULL }
};
