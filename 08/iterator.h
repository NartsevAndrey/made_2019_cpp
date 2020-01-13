#pragma once

#include <iterator>
#include <stdexcept>

template <class T>
class Iterator
	: public std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, T*, T&>
{
public:
	explicit Iterator(T* ptr)
		: ptr_(ptr)
	{
	}

	T& operator*() const
	{
		return *ptr_;
	}

	T* operator->() const
	{
		return ptr_;
	}

	bool operator==(const Iterator<T>& other) const
	{
		return ptr_ == other.ptr_;
	}

	bool operator!=(const Iterator<T>& other) const
	{
		return !(*this == other);
	}

	bool operator<(const Iterator<T>& other) const
	{
		ptrdiff_t diff = other.ptr_ - ptr_;
		return diff > 0;
	}

	bool operator>(const Iterator<T>& other) const
	{
		return other < *this;
	}

	bool operator<=(const Iterator<T>& other) const
	{
		return !(*this > other);
	}

	bool operator>=(const Iterator<T>& other) const
	{
		return !(*this < other);
	}

	Iterator& operator++()
	{
		++ptr_;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator tmp = *this;
		++ptr_;
		return tmp;
	}

	Iterator& operator--()
	{
		--ptr_;
		return *this;
	}

	Iterator operator--(int)
	{
		Iterator tmp(*this);
		--ptr_;
		return tmp;
	}

	Iterator& operator+=(ptrdiff_t n)
	{
		ptr_ += n;
		return *this;
	}

	Iterator operator+(ptrdiff_t n) const
	{
		Iterator tmp = *this;
		return tmp += n;
	}

	Iterator& operator-=(ptrdiff_t n)
	{
		ptr_ -= n;
		return *this;
	}

	Iterator operator-(ptrdiff_t n) const
	{
		Iterator tmp = *this;
		return tmp -= n;
	}

	T& operator[](ptrdiff_t n) const
	{
		return *(*this + n);
	}

	T*& operator()()
	{
		return ptr_;
	}

private:
	T* ptr_;

	void ptr_validation(T* ptr) const
	{
		if (ptr == nullptr)
		{
			throw std::runtime_error("Using null pointer as iterator");
		}
	}
};
