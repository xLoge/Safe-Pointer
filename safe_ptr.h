#include <ostream>

#pragma once

#ifndef SAFE_PTR
#define SAFE_PTR

template<class T>
class safe_ptr
{
private:
	T* m_Var;

public:
	safe_ptr()
		:m_Var(new T)
	{

	}

	safe_ptr(T* ptr, bool reuse)
		: m_Var(ptr)
	{
		if (!reuse)
			*this->m_Var = *ptr;
	}

	safe_ptr(const T var)
		: m_Var(new T(var))
	{

	}

	safe_ptr(const safe_ptr<T>& s_ptr)
		: m_Var(new T(s_ptr.cget()))
	{

	}

	~safe_ptr()
	{
		if (m_Var) {
			delete m_Var;
		}
	}

	T* get()
	{
		return this->m_Var;
	}

	void swap(safe_ptr<T>& other)
	{
		const T new_val = other.cget();
		other = *this->m_Var;
		*this->m_Var = new_val;
	}

	void reset()
	{
		delete this->m_Var;
		m_Var = new T;
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

	void operator=(T val)
	{
		*this->m_Var = val;
	}

	void operator=(T* ptr)
	{
		delete this->m_Var;
		this->m_Var = ptr;
	}

	T operator*() const
	{
		return *this->m_Var;
	}

	T operator()() const
	{
		return *this->m_Var;
	}

	T operator[](size_t idx) const
	{
		return *this->m_Var[idx];
	}

	bool operator==(const T val) const
	{
		return *this->m_Var == val;
	}

	bool operator==(const safe_ptr<T>& val) const
	{
		return *this->m_Var == *val.m_Var;
	}

	bool operator!=(const T val) const
	{
		return *this->m_Var != val;
	}

	bool operator!=(const safe_ptr<T>& val) const
	{
		return *this->m_Var != *val.m_Var;
	}

	operator bool() const
	{
		return (bool)*this->m_Var;
	}
};

template<class T>
std::ostream& operator<<(std::ostream& out, const safe_ptr<T>& ptr)
{
	return out << ptr.cget();
}

#endif
