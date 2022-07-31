#pragma once
#include<cassert>
#include<ctime>
#include <cstdlib>
#include< algorithm >
template <typename T> 
class Stack
{
private:
	int m_size;
	const int m_capacity;
	T* m_arr;
	int getRandomNumber(int min, int max)
	{
		static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };  // static used for efficiency, so we only calculate this value once
		// evenly distribute the random number across our range
		return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
	}
public:
	Stack(int capacity, int size = 0) : m_size{ size }, m_capacity{ capacity }
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		std::rand();
		assert((capacity > 0) && "Error: Capacity must be larger than 0");
		m_arr = new T[capacity];
	}
	Stack(const Stack& other) : Stack{ other.capacity() , other.size()}
	{
		for (int i{ 0 }; i < other.size(); ++i)
		{
			m_arr[i] = other.m_arr[i];
		}
	}
	~Stack()
	{
		delete[] m_arr;
	}
	bool empty() const
	{
		return (m_size == 0);
	}
	T& peek() const
	{
		return m_arr[m_size - 1];
	}
	T& pop()
	{
		T& temp = peek();
		--m_size;
		return temp;
	}
	int size() const
	{
		return m_size;
	}
	const int capacity() const
	{
		return m_capacity;
	}
	void push(const T& item)
	{
		if (m_size < m_capacity)
		{
			++m_size;
			m_arr[m_size - 1] = item;
		}

	}
	void shuffle()
	{
		for (int i{ 0 }; i < m_size; ++i)
		{
			int randIndex{ getRandomNumber(i, m_size - 1) };
			std::swap(m_arr[i], m_arr[randIndex]);
		}
	}

};

