#pragma once

#include <iostream>
#include <algorithm>

class BigInt
{
public:
	template<typename T>
	BigInt(T num);

	BigInt(const char* number, size_t size);
	BigInt(const BigInt& copied);
	BigInt(BigInt&& moved);

	~BigInt();

	BigInt& operator=(const BigInt& copied);
	BigInt& operator=(BigInt&& moved);

	friend std::ostream& operator << (std::ostream& os, const BigInt& num);

	bool operator ==(const BigInt& other) const;
	bool operator <(const BigInt& other) const;
	bool operator !=(const BigInt& other) const;
	bool operator >(const BigInt& other) const;
	bool operator <=(const BigInt& other) const;
	bool operator >=(const BigInt& other) const;

	BigInt operator-() const;

	BigInt operator+(const BigInt& other) const;
	BigInt operator-(const BigInt& other) const;

	BigInt operator+=(const BigInt& right);
	BigInt operator-=(const BigInt& right);

	template<typename T>
	friend bool operator ==(const BigInt& left, T right);
	template<typename T>
	friend bool operator ==(T left, const BigInt& right);
	template<typename T>
	friend bool operator <(const BigInt& left, T right);
	template<typename T>
	friend bool operator <(T left, const BigInt& right);

	template<typename T, typename Y>
	friend bool operator !=(const T&& left, const Y&& right);
	template<typename T, typename Y>
	friend bool operator >(const T&& left, const Y&& right);
	template<typename T, typename Y>
	friend bool operator <=(const T&& left, const Y&& right);
	template<typename T, typename Y>
	friend bool operator >=(const T&& left, const Y&& right);

	template<typename T>
	friend BigInt operator+(const BigInt& left, T right);
	template<typename T>
	friend BigInt operator-(const BigInt& left, T right);

	template<typename T>
	friend BigInt operator+(T left, const BigInt& right);
	template<typename T>
	friend BigInt operator-(T left, const BigInt& right);

	template<typename T>
	friend BigInt operator+=(BigInt& left, T right);
	template<typename T>
	friend BigInt operator-=(BigInt& left, T right);

private:
	size_t size_;
	char* number_;
	bool isNegative_;

	// Количество разрядов в числе
	template<typename T>
	int byteCount(T x) const;

	// Проверка на равенство нулю
	bool isZero() const;

	BigInt(const char* number, size_t size, bool isNegative);
};

template<typename T>
BigInt::BigInt(T num)
{
	static_assert(std::is_integral<T>::value, "Integer type required");
	isNegative_ = num < 0;
	if (isNegative_)
		num *= -1;
	size_ = byteCount(num);
	number_ = new char[size_];
	for (size_t i = 0; i < size_; i++)
	{
		number_[i] = (char)(num % 10);
		num /= 10;
	}
}

template<typename T>
bool operator==(const BigInt& left, T right)
{
	return left == BigInt(right);
}

template<typename T>
bool operator==(T left, const BigInt& right)
{
	return BigInt(left) == right;
}

template<typename T>
bool operator<(const BigInt& left, T right)
{
	return left < BigInt(right);
}

template<typename T>
bool operator<(T left, const BigInt& right)
{
	return BigInt(left) < right;
}

template<typename T, typename Y>
bool operator<=(const T&& left, const Y&& right)
{
	return (left < right || left == right);
}

template<typename T, typename Y>
bool operator!=(const T&& left, const Y&& right)
{
	return !(left == right);
}

template<typename T, typename Y>
bool operator>(const T&& left, const Y&& right)
{
	return !(left <= right);
}

template<typename T, typename Y>
bool operator>=(const T&& left, const Y&& right)
{
	return !(left < right);
}

template<typename T>
BigInt operator+(const BigInt& left, T right)
{
	return left + BigInt(right);
}

template<typename T>
BigInt operator-(const BigInt& left, T right)
{
	return left - BigInt(right);
}

template<typename T>
BigInt operator+(T left, const BigInt& right)
{
	return BigInt(left) + right;
}

template<typename T>
BigInt operator-(T left, const BigInt& right)
{
	return BigInt(left) - right;
}

template<typename T>
BigInt operator+=(BigInt& left, T right) {
	BigInt tmp(left);
	left += BigInt(right);
	return tmp;
}

template<typename T>
BigInt operator-=(BigInt& left, T right) {
	BigInt tmp(left);
	left -= BigInt(right);
	return tmp;
}

template<typename T>
int BigInt::byteCount(T x) const {
	size_t p = 10;
	size_t t = x;
	for (int i = 1; i < 20; i++) {
		if (t < p)
			return i;
		p = 10 * p;
	}
	return 20;
}
