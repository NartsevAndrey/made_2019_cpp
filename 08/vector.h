#pragma once

#include <iterator>
#include <stdexcept>
#include <new>
#include "allocator.h"
#include "iterator.h"

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
	using value_type = T;
	using allocator_type = Allocator<T>;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = value_type & ;
	using const_reference = const value_type&;
	using pointer = T * ;
	using const_pointer = const T*;
	using iterator = Iterator<T>;
	using reverse_iterator = std::reverse_iterator<iterator>;

	Vector(const Alloc& alloc = Allocator<T>())
		: alloc_(alloc)
		, begin_(alloc_.allocate(0))
		, end_(begin_)
		, last_(begin_)
		, size_(0)
		, capacity_(0)
	{
	}

	explicit Vector(size_t count, const Alloc& alloc = Allocator<T>())
		: alloc_(alloc)
		, begin_(alloc_.allocate(count))
		, end_(begin_ + count)
		, last_(begin_ + count)
		, size_(count)
		, capacity_(count)
	{
		construct(begin_, end_, T());
	}

	Vector(size_t count, const T& defaultValue, const Alloc& alloc = Allocator<T>())
		: alloc_(alloc)
		, begin_(alloc_.allocate(count))
		, end_(begin_ + count)
		, last_(begin_ + count)
		, size_(count)
		, capacity_(count)
	{
		construct(begin_, end_, defaultValue);
	}

	Vector(const Vector& other)
		: begin_(alloc_.allocate(0))
		, end_(begin_)
		, last_(begin_)
		, size_(0)
		, capacity_(0)
	{
		reserve(other.size_);
		for (auto it = other.begin_; it != other.end_; it++)
		{
			push_back(*it);
		}
	}

	Vector& operator=(const Vector& other)
	{
		if (this == &other)
			return *this;

		reserve(other.capacity_);
		destroy(begin_, end_);

		capacity_ = other.capacity_;
		size_ = 0;
		end_ = begin_;
		for (auto it = other.begin_; it != other.end_; it++)
			push_back(*it);

		return *this;
	}

	Vector(Vector&& other)
		: begin_(other.begin_)
		, end_(other.end_)
		, last_(other.last_)
		, size_(other.size_)
		, capacity_(other.capacity_)
	{
		other.begin_() = nullptr;
		other.end_() = nullptr;
		other.last_() = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}


	Vector& operator=(Vector&& other)
	{
		if (this == &other)
			return *this;

		alloc_.deallocate(begin_(), capacity_);

		begin_ = other.begin_;
		end_ = other.end_;
		last_ = other.last_;
		size_ = other.size_;
		capacity_ = other.capacity_;

		other.begin_() = nullptr;
		other.end_() = nullptr;
		other.last_() = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;

		return *this;
	}

	Vector(std::initializer_list<T> init)
		: begin_(alloc_.allocate(init.size()))
		, end_(begin_ + init.size())
		, last_(begin_ + init.size())
		, size_(init.size())
		, capacity_(init.size())
	{
		size_t i = 0;
		auto current = init.begin();
		const auto end = init.end();
		while (current != end)
			begin_[i++] = *current++;
	}

	~Vector()
	{
		alloc_.deallocate(begin_(), capacity_);
	}

	iterator begin() noexcept
	{
		return begin_;
	}

	iterator end() noexcept
	{
		return end_;
	}

	reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(end_);
	}

	reverse_iterator rend() noexcept
	{
		return reverse_iterator(begin_);
	}

	void push_back(const T& value)
	{
		if (size_ >= capacity_)
		{
			size_t newSize = calculate_expansion_size(size_ + 1);
			reserve(newSize);
		}
		*(end_()) = value;
		size_++;
		end_++;
	}

	void push_back(T&& value)
	{
		if (size_ >= capacity_)
		{
			size_t newSize = calculate_expansion_size(size_ + 1);
			reserve(newSize);
		}
		*(end_()) = std::move(value);
		size_++;
		end_++;
	}

	void pop_back()
	{
		if (size_ == 0)
			throw std::runtime_error("Vector empty before pop_back");
		destroy(end_ - 1, end_);
		end_--;
		size_--;
	}

	T& operator[](size_t pos)
	{
		if (pos >= size_)
			throw std::runtime_error("Vector subscript out of range");
		return begin_[pos];
	}

	const T& operator[](size_t pos) const
	{
		if (pos >= size_)
			throw std::runtime_error("Vector subscript out of range");
		return begin_[pos];
	}

	bool empty() const noexcept
	{
		return !size_;
	}

	size_t size() const noexcept
	{
		return size_;
	}

	size_t capacity() const noexcept
	{
		return capacity_;
	}

	void clear() noexcept
	{
		destroy(begin_, end_);
		end_ = begin_;
		size_ = 0;
	}

	void resize(size_t newSize)
	{
		resize(newSize, T());
	}

	void resize(size_t newSize, const T& defaultValue)
	{
		if (newSize > capacity_)
		{
			size_t newCapacity = calculate_expansion_size(newSize);
			reserve(newCapacity);
			construct(begin_ + size_, end_, defaultValue);
		}
		else if (newSize > size_)
		{
			iterator old_end = end_;
			end_ = begin_ + newSize;
			construct(old_end, end_, defaultValue);
		}
		else if (newSize < size_)
		{
			end_ = begin_ + newSize;
			destroy(end_, begin_ + size_);
		}
		size_ = newSize;
	}

	void reserve(size_t newCapacity)
	{
		if (newCapacity > capacity_)
		{
			if (newCapacity > alloc_.max_size())
				throw std::runtime_error("Attempt to allocate too much memory");

			T* newVector = alloc_.allocate(newCapacity);

			T* pointer = newVector;
			for (iterator it = begin_; it != end_; it++)
			{
				*pointer = *it;
				pointer++;
			}

			alloc_.deallocate(begin_(), capacity_);

			begin_() = newVector;
			end_() = newVector + size_;
			last_() = newVector + newCapacity;
			capacity_ = newCapacity;
		}
	}

private:
	Alloc alloc_;
	iterator begin_; // итератор на начало вектора
	iterator end_; // итератор, указывающий на первый, после последнего эелемента
	iterator last_; // итератор, указывающий на первый, после конца зарезервированной пам¤ти
	size_t size_; // размер вектора
	size_t capacity_; // размер зарезервированной пам¤ти

	void destroy(const iterator& first, const iterator& last)
	{
		if (std::is_destructible<T>::value)
		{
			for (iterator it = first; it != last; it++)
			{
				it()->~T();
			}
		}
	}

	size_t calculate_expansion_size(size_t new_size)
	{
		if (new_size > alloc_.max_size() - new_size / 2)
		{
			return new_size;
		}

		size_t expansion_size = size_ + size_ / 2;
		if (expansion_size < new_size)
		{
			return new_size;
		}

		return expansion_size;
	}

	void construct(iterator first, iterator last, const T& value)
	{
		for (iterator it = first; it != last; it++)
			alloc_.construct(it(), value);
	}
};
