#include <sstream>
#include "serializer.h"
#include "testing.h"

struct Data
{
	uint64_t a;
	bool b;
	uint64_t c;
	
	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c);
	}
};

struct Data1
{
	uint64_t a;
	bool b;
	
	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b);
	}
};

struct Data2
{
	uint64_t a;
	bool b;
	bool c;
	
	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c);
	}
};

template <typename T, typename Y>
Error test(T& x, Y& y)
{
	std::stringstream stream;
	
	Serializer serializer(stream);
	serializer.save(x);
	
	Deserializer deserializer(stream);
	const Error err = deserializer.load(y);
	return err;
}


void test_1(void)
{
	Data x { 1, true, 2 };
	Data y { 0, false, 3};
	
	Error err = test(x, y);
	TEST_CHECK(err == Error::NoError);
	TEST_CHECK(x.a == y.a);
	TEST_CHECK(x.b == y.b);
	TEST_CHECK(x.c == y.c);
}

void test_2(void)
{
	Data x { 1, true, 2 };
	Data2 y { 0, false, false};
	
	Error err = test(x, y);
	TEST_CHECK(err == Error::CorruptedArchive);
}

void test_3(void)
{
	Data x { 1, true, 2 };
	Data1 y { 0, false};
	
	Error err = test(x, y);
	TEST_CHECK(err == Error::CorruptedArchive);
}

void test_4(void)
{
	Data1 x { 0, false};
	Data y { 1, true, 2 };
	
	Error err = test(x, y);
	TEST_CHECK(err == Error::CorruptedArchive);
}

			   
TEST_LIST = {
   { "test_1", test_1 },
   { "test_2", test_2 },
   { "test_3", test_3 },
   { "test_4", test_4 },
   { NULL, NULL }
};
