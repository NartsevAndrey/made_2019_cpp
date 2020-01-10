#include "bigint.h"

BigInt::BigInt(const char* number, size_t size)
{
	size_t i = 0;
	if (size > 0 && (number[0] == '-' || number[0] == '+'))
	{
		isNegative_ = bool(number[0] == '-');
		i++;
	}
	else
		isNegative_ = false;

	while (i < size - 1 && number[i] == '0')
		i++;

	size_ = size - i;
	number_ = new char[size_];
	for (size_t j = 0; j < size_; j++)
		number_[(int)size_ - 1 - j] = number[i + j] - '0';
}

BigInt::BigInt(const BigInt& copied)
	: number_(new char[copied.size_])
	, size_(copied.size_)
	, isNegative_(copied.isNegative_)

{
	std::copy(copied.number_, copied.number_ + size_, number_);
}

BigInt::BigInt(BigInt&& moved)
	: number_(moved.number_)
	, size_(moved.size_)
	, isNegative_(moved.isNegative_)
{
	moved.number_ = nullptr;
	moved.size_ = 0;
}

BigInt::BigInt(const char* number, size_t size, bool isNegative)
	: number_(new char[size])
	, size_(size)
	, isNegative_(isNegative)
{
	std::copy(number, number + size_, number_);
}

BigInt::~BigInt()
{
	delete[] number_;
}

bool BigInt::isZero() const
{
	return (size_ == 1 && number_[0] == 0);
}

BigInt& BigInt::operator=(const BigInt& copied)
{
	if (this == &copied)
		return *this;
	char* ptr = new char[copied.size_];
	delete[] number_;
	number_ = ptr;
	size_ = copied.size_;
	isNegative_ = copied.isNegative_;
	std::copy(copied.number_, copied.number_ + size_, number_);
	return *this;
}

BigInt& BigInt::operator=(BigInt&& moved)
{
	if (this == &moved)
		return *this;
	delete[] number_;
	number_ = moved.number_;
	size_ = moved.size_;
	isNegative_ = moved.isNegative_;
	moved.number_ = nullptr;
	moved.size_ = 0;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const BigInt& num)
{
	if (num.isZero())
		return os << 0;

	if (num.isNegative_)
		os << "-";

	for (int i = (int)num.size_ - 1; i >= 0; i--)
		os << (int)num.number_[i];
	return os;
}

bool BigInt::operator==(const BigInt& other) const
{
	if (this == &other)
		return true;

	if (isNegative_ != other.isNegative_ || size_ != other.size_)
		return false;

	if (isZero() && other.isZero())
		return true;

	for (size_t i = 0; i < other.size_; i++)
		if (number_[i] != other.number_[i])
			return false;
	return true;
}

bool BigInt::operator<(const BigInt& other) const
{
	if (*this == other)
		return false;

	if (isNegative_ && !other.isNegative_)
		return true;

	if (!isNegative_ && other.isNegative_)
		return false;

	if (size_ != other.size_)
		return size_ < other.size_;

	bool isLess = true;
	for (int i = (int)size_ - 1; i >= 0; i--) {
		if (number_[i] != other.number_[i]) {
			isLess = number_[i] < other.number_[i];
			break;
		}
	}
	return isLess && !isNegative_ || !isLess && isNegative_;
}

bool BigInt::operator!=(const BigInt& right) const
{
	return !(*this == right);
}

bool BigInt::operator<=(const BigInt& right) const
{
	return (*this < right || *this == right);
}

bool BigInt::operator>(const BigInt& right) const
{
	return !(*this <= right);
}

bool BigInt::operator>=(const BigInt& right) const
{
	return !(*this < right);
}

BigInt BigInt::operator-() const
{
	BigInt tmp(*this);
	tmp.isNegative_ = !isNegative_;
	return tmp;
}

BigInt BigInt::operator+(const BigInt& other) const
{
	if (isNegative_)
	{
		if (other.isNegative_)
			return -(-*this + (-other));
		else
			return other - (-*this);
	}
	else if (other.isNegative_)
		return *this - (-other);
	else if (*this < other)
		return (other + *this);

	// Знаем, что оба числа положительные
	char* resultNum = new char[size_ + 1];
	int carry = 0;
	size_t resultSize = size_;
	for (size_t i = 0; i < size_ || carry; i++) {
		if (i == size_) {
			resultSize++;
			resultNum[i] = carry + (i < other.size_ ? other.number_[i] : 0);
		}
		else {
			resultNum[i] = number_[i] + carry +
				(i < other.size_ ? other.number_[i] : 0);
		}
		carry = resultNum[i] >= 10;
		if (carry)
			resultNum[i] -= 10;
	}
	BigInt result = BigInt(resultNum, resultSize, false);
	delete[] resultNum;
	return result;
}

BigInt BigInt::operator-(const BigInt& other) const
{
	if (other.isNegative_)
		return (*this + (-other));
	else if (this->isNegative_)
			return -(-*this + other);
	else if (*this < other)
			return -(other - *this);

	// Предполагаем, что уменьшаемое не меньше вычитаемого
	BigInt tmp(*this);
	int carry = 0;
	for (size_t i = 0; i < other.size_ || carry; i++)
	{
		tmp.number_[i] -= carry + (i < other.size_ ? other.number_[i] : 0);
		carry = tmp.number_[i] < 0;
		if (carry)
			tmp.number_[i] += 10;
	}

	size_t i = size_ > 0 ? size_ - 1 : 0;
	while (i > 0 && tmp.number_[i] == 0)
		i--;

	return BigInt(tmp.number_, i + 1, false);
}

BigInt BigInt::operator+=(const BigInt& right) {
	BigInt tmp(*this);
	*this = *this + right;
	return tmp;
}

BigInt BigInt::operator-=(const BigInt& right) {
	BigInt tmp(*this);
	*this = *this - right;
	return tmp;
}
