#pragma once
#include <limits>

template <class T>
class Allocator
{
public:
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = T&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;

	T* allocate(size_t count)
	{
		T* ptr = static_cast<T*>(malloc(get_size(count)));
		if (ptr == nullptr)
			throw std::bad_alloc();
		return ptr;
	}

	template<class U, class... Args >
	void construct(U* p, Args&&... args)
	{
		new((void*)p) U(std::forward<Args>(args)...);
	}

	template< class U >
	void destroy(U* p)
	{
		p->~U();
	}

	void deallocate(T* ptr, size_t count)
	{
		::operator delete(ptr, get_size(count));
	}

	size_t max_size() const noexcept
	{
		return std::numeric_limits<size_t>::max() / sizeof(T);
	}

private:
	size_t get_size(size_t n) const noexcept
	{
		return sizeof(T) * n;
	}
};
