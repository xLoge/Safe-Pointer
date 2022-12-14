#include <ostream>
#include <memory>

#pragma once

#ifndef SAFE_PTR
#define SAFE_PTR

template<class T>
class safe_ptr
{
private:
	T* m_Var; // The holy pointer

public:
	safe_ptr()
		: m_Var(new T{ })
	{

	}

	safe_ptr(T* ptr, const bool use = true)
		: m_Var(ptr)
	{
		if (!std::move(use))
		{
			this->m_Var = new T(*ptr);
		}
	}

	safe_ptr(safe_ptr<T>& ptr)
		: m_Var(new T(ptr.cget()))
	{

	}

	safe_ptr(std::unique_ptr<T> ptr)
		: m_Var(new T(*ptr.get()))
	{

	}

	safe_ptr(std::shared_ptr<T> ptr)
		: m_Var(new T(*ptr.get()))
	{

	}

	template <class... Args>
	safe_ptr(Args&&... args)
		: m_Var(new T(args...))
	{

	}

	~safe_ptr()
	{
		if (this->m_Var) { delete this->m_Var; this->m_Var = nullptr; }
	}

	void swap(safe_ptr<T>& right)
	{
		std::swap(*this->m_Var, *right.m_Var);
	}

	void swap_ptr(safe_ptr<T>& right)
	{
		std::swap(this->m_Var, right.m_Var);
	}

	void reset()
	{
		if (this->m_Var) { delete this->m_Var; }
		this->m_Var = new T(0);
	}

	void destroy()
	{
		if (this->m_Var) { delete this->m_Var; this->m_Var = nullptr; }
	}

	T* get()
	{
		return this->m_Var;
	}

	T cget() const
	{
		return *this->m_Var;
	}

	T* operator->()
	{
		return this->m_Var;
	}

	T* operator()()
	{
		return this->m_Var;
	}

	T operator*() const
	{
		return *this->m_Var;
	}

	T operator()() const
	{
		return *this->m_Var;
	}

	T operator[](const size_t idx) const
	{
		return *this->m_Var[std::move(idx)];
	}

	void operator=(T val)
	{
		*this->m_Var = std::move(val);
	}

	void operator=(T* ptr)
	{
		delete this->m_Var;
		this->m_Var = ptr;
	}

	void operator=(safe_ptr<T>& ptr)
	{
		*this->m_Var = *ptr.get();
	}

	void operator=(std::unique_ptr<T>& ptr)
	{
		*this->m_Var = *ptr.get();
	}

	void operator=(std::shared_ptr<T>& ptr)
	{
		*this->m_Var = *ptr.get();
	}

	bool operator==(const T val) const
	{
		return *this->m_Var == std::move(val);
	}

	bool operator==(const safe_ptr<T>& val) const
	{
		return *this->m_Var == *val.m_Var;
	}

	bool operator!=(const T val) const
	{
		return *this->m_Var != std::move(val);
	}

	bool operator!=(const safe_ptr<T>& val) const
	{
		return *this->m_Var != *val.m_Var;
	}

	operator bool() const
	{
		return this->m_Var != nullptr;
	}
};

template<class T>
std::ostream& operator<<(std::ostream& out, safe_ptr<T>& ptr)
{
	return out << ptr.get();
}

#endif
