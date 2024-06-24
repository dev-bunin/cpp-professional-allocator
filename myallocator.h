#ifndef MYALLOCATOR_H
#define MYALLOCATOR_H

#include <cstdlib>
#include <new>
#include <type_traits>
#include <algorithm>

template <class T>
class MyAllocator {
public:
	using value_type = T;
	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;

	MyAllocator() = default;

	MyAllocator (std::size_t size) noexcept
		: m_size(size)
	{
	}

	MyAllocator(const MyAllocator & a) noexcept
		: MyAllocator(a.m_size) {
	}

	template <class U>
	MyAllocator(const MyAllocator <U>& a) noexcept
	: MyAllocator(a.getSize()){
	}

	~MyAllocator() {
		free(m_pool);
	}

	MyAllocator select_on_container_copy_construction() {
		return MyAllocator(m_size);
	}

	T* allocate (std::size_t n)
	{
		if (m_pool == nullptr) {
			m_pool = malloc(n > m_size ? n : m_size);
		}
		if (m_pos + n > m_size) {
			// Места не хватило. Выделить бы
			size_t newSize = m_size == 0 ? 1 : m_size * 2;
			void *newPool = malloc(sizeof(T) * newSize);
			std::move(static_cast<T*>(m_pool), static_cast<T*>(m_pool) + m_pos, static_cast<T*>(newPool));

			std::swap(m_size, newSize);
			std::swap(m_pool, newPool);
		}
		std::size_t currPos = m_pos;
		m_pos += n;
		return static_cast<T*>(m_pool) + currPos; //dummy implementation
	}

	void deallocate (T*, std::size_t)
	{
	}

	std::size_t getSize() const {
		return m_size;
	}

private:
	std::size_t m_pos = 0;
	std::size_t m_size = 0;
	void *m_pool = nullptr;
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
