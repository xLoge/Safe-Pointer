#pragma once

#include <ostream>

#ifndef SAFE_PTR
#define SAFE_PTR

namespace fst
{
	template<class T>
	class safe_ptr
	{
	private:
		T* m_Ptr = nullptr;
		bool m_IsChildClass = false;
		bool m_Deleted = false;

	public:
		bool m_Delete = true;

	public:
		constexpr safe_ptr() = default;

		constexpr safe_ptr(const T val)
			: m_Ptr(new T(val))
		{

		}

		constexpr safe_ptr(T* ptr)
			: m_Ptr(ptr)
		{

		}

		explicit constexpr safe_ptr(T* ptr, bool copy_val = false)
			: m_Ptr(ptr)
		{
			if (copy_val)
			{
				this->m_Ptr = new T(*ptr);
			}
		}

		constexpr safe_ptr(std::unique_ptr<T> ptr)
			: m_Ptr(ptr.get()), m_IsChildClass(true)
		{

		}

		constexpr safe_ptr(std::shared_ptr<T> ptr)
			: m_Ptr(ptr.get()), m_IsChildClass(true)
		{

		}

		constexpr safe_ptr(safe_ptr<T>& ptr)
			: m_Ptr(ptr.m_Ptr), m_IsChildClass(true)
		{

		}

		template <class... Args>
		explicit constexpr safe_ptr(Args&&... args)
			: m_Ptr(new T(std::move(args...)))
		{

		}

		~safe_ptr()
		{
			if (this->m_Ptr && !this->m_IsChildClass && !this->m_Deleted && this->m_Delete)
			{
				delete this->m_Ptr;
			}
		}

		constexpr void init()
		{
			if (!m_Ptr) {
				m_Ptr = new T{ };
			}
		}

		constexpr void swap(safe_ptr<T>& right)
		{
			std::swap(*this->m_Ptr, *right.m_Ptr);
		}

		constexpr void swap_ptr(safe_ptr<T>& right)
		{
			std::swap(this->m_Ptr, right.m_Ptr);
		}

		constexpr void reset()
		{
			if (this->m_Ptr && !this->m_Deleted && this->m_Delete) {
				delete this->m_Ptr;
			}
			this->m_Ptr = new T{ };
			this->m_Deleted = false;
		}

		constexpr void destroy()
		{
			if (this->m_Ptr && !this->m_Deleted && this->m_Delete) {
				delete this->m_Ptr;
				this->m_Deleted = true;
			}
		}

		constexpr T* get()
		{
			return this->m_Ptr;
		}

		constexpr T* get() const
		{
			return this->m_Ptr;
		}

		constexpr T cget() const
		{
			return *this->m_Ptr;
		}

		constexpr T* operator->()
		{
			return this->m_Ptr;
		}

		constexpr T* operator()()
		{
			return this->m_Ptr;
		}

		constexpr T operator*() const
		{
			return *this->m_Ptr;
		}

		constexpr T operator()() const
		{
			return *this->m_Ptr;
		}

		constexpr T& operator[](const size_t idx) const
		{
			return this->m_Ptr[idx];
		}

		constexpr void operator=(T val)
		{
			*this->m_Ptr = val;
		}

		constexpr void operator=(const T& val)
		{
			*this->m_Ptr = val;
		}

		constexpr void operator=(T* ptr)
		{
			if (this->m_Ptr && !this->m_Deleted && this->m_Delete)
			{
				delete this->m_Ptr;
			}
			this->m_Ptr = ptr;
			this->m_Deleted = false;
		}

		constexpr void operator=(safe_ptr<T>& ptr)
		{
			*this->m_Ptr = *ptr.m_Ptr;
		}

		constexpr void operator=(std::unique_ptr<T>& ptr)
		{
			*this->m_Ptr = *ptr.get();
		}

		constexpr void operator=(std::shared_ptr<T>& ptr)
		{
			*this->m_Ptr = *ptr.get();
		}

		constexpr bool operator==(T val) const
		{
			return *this->m_Ptr == val;
		}

		constexpr bool operator==(const T& val) const
		{
			return *this->m_Ptr == val;
		}

		constexpr bool operator==(const safe_ptr<T>& val) const
		{
			return *this->m_Ptr == *val.m_Ptr;
		}

		constexpr bool operator!=(T val) const
		{
			return *this->m_Ptr != val;
		}

		constexpr bool operator!=(const T& val) const
		{
			return *this->m_Ptr != val;
		}

		constexpr bool operator!=(const safe_ptr<T>& val) const
		{
			return *this->m_Ptr != *val.m_Ptr;
		}

		constexpr operator bool() const
		{
			return this->m_Ptr != nullptr;
		}
	};
}

template<class T>
constexpr std::ostream& operator<<(std::ostream& out, fst::safe_ptr<T>& ptr)
{
	return out << ptr.get();
}

#endif
