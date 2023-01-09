#include <ostream>
#include <memory>

#pragma once

#ifndef SAFE_PTR
#define SAFE_PTR

template<class T>
class safe_ptr
{
private:
	T* m_Ptr;
	bool m_IsChildClass = false;

public:
	constexpr safe_ptr()
		: m_Ptr(new T{ })
	{
		
	}
	
	constexpr safe_ptr(T&& val)
		: m_Ptr(new T(std::move(val)))
	{

	}

	constexpr safe_ptr(T* ptr)
		: m_Ptr(ptr)
	{

	}

	explicit constexpr safe_ptr(T* ptr, bool copy_val = false)
		: m_Ptr(ptr)
	{
		if (std::move(copy_val))
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
		: m_Ptr(ptr.get()), m_IsChildClass(true)
	{
		
	}

	template <class... Args>
	explicit constexpr safe_ptr(Args&&... args)
		: m_Ptr(new T(std::move(args...)))
	{

	}

	constexpr ~safe_ptr()
	{
		if (this->m_Ptr != nullptr && this->m_IsChildClass == false)
		{ 
			delete this->m_Ptr;
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
		if (this->m_Ptr != nullptr) {
			delete this->m_Ptr;
		}
		this->m_Ptr = new T{ };
	}

	constexpr void destroy()
	{
		if (this->m_Ptr != nullptr) {
			delete this->m_Ptr;
		}
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

	constexpr T& operator[](size_t idx) const
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
		delete this->m_Ptr;
		this->m_Ptr = ptr;
	}

	constexpr void operator=(safe_ptr<T>& ptr)
	{
		*this->m_Ptr = *ptr.get();
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
		return *this->m_Ptr != std::move(val);
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

template<class T>
constexpr std::ostream& operator<<(std::ostream& out, safe_ptr<T>& ptr)
{
	return out << ptr.get();
}

#endif