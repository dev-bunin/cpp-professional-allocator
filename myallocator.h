#ifndef MYALLOCATOR_H
#define MYALLOCATOR_H

#include <cstdlib>
#include <new>
#include <type_traits>

template <class T>
struct MyAllocator {
	std::size_t m_pos = 0;
	std::size_t m_size = 0;
	void *m_pool = nullptr;

	using value_type = T;

	MyAllocator() = delete;

	MyAllocator (std::size_t size) noexcept
		: m_size(size),
		  m_pool(malloc(sizeof(T) * m_size))
	{
	}


	MyAllocator(const MyAllocator & a) noexcept
		: MyAllocator(a.m_size) {
	}

	template <class U>
	MyAllocator(const MyAllocator <U>& a) noexcept
	: MyAllocator(a.m_size){
	}

	~MyAllocator() {
		free(m_pool);
	}

	MyAllocator select_on_container_copy_construction() {
		return MyAllocator(m_size);
	}

	T* allocate (std::size_t n)
	{
		if (m_pos + n > m_size) {
			throw std::bad_alloc();
		}
		std::size_t currPos = m_pos;
		m_pos += n;
		return static_cast<T*>(m_pool) + currPos; //dummy implementation
	}

	void deallocate (T*, std::size_t)
	{
	}

	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;
};

template <class T, class U>
constexpr bool operator== (const MyAllocator<T>& a1, const MyAllocator<U>& a2) noexcept
{
	return a1.m_pool == a2.m_pool;
}

template <class T, class U>
constexpr bool operator!= (const MyAllocator<T>& a1, const MyAllocator<U>& a2) noexcept
{
	return a1.m_pool != a2.m_pool;
}

#endif // MYALLOCATOR_H
