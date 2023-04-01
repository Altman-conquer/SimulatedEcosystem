#pragma once
#include <xutility>
#include "Utility.h"
#include "exception"
using std::iterator;

template<typename T>
class DynamicArrayList {
public:
	DynamicArrayList() :data(nullptr), _size(0), capacity(0) {}

	DynamicArrayList(int n) : data(new T[n]), _size(0), capacity(n) {}

	DynamicArrayList(const DynamicArrayList& other) : data(new T[other.capacity]), _size(other._size), capacity(other.capacity)
	{
		MemoryCopy(data, other.data, _size * sizeof(T));
	}

	DynamicArrayList(DynamicArrayList&& other) : data(other.data), _size(other._size), capacity(other.capacity)
	{
		other.data = nullptr;
		other._size = other.capacity = 0;
	}

	class DynamicArrayListIterator : public std::iterator<std::forward_iterator_tag, T> {
	public:
		// Constructor
		DynamicArrayListIterator(T* p) : ptr(p) {}

		// Dereference operator
		T& operator*() { return *ptr; }

		// Increment operator (prefix)
		DynamicArrayListIterator& operator++() { ptr++; return *this; }

		// Increment operator (postfix)
		DynamicArrayListIterator operator++(int) { DynamicArrayListIterator temp = *this; ptr++; return temp; }

		// Decrement operator (prefix)
		DynamicArrayListIterator& operator--() { ptr--; return *this; }

		// Decrement operator (postfix)
		DynamicArrayListIterator operator--(int) { DynamicArrayListIterator temp = *this; ptr--; return temp; }

		size_t operator-(const DynamicArrayListIterator& other) const { return ptr - other.ptr; };

		// Equality operator
		bool operator==(const DynamicArrayListIterator& other) const { return ptr == other.ptr; }

		// Inequality operator
		bool operator!=(const DynamicArrayListIterator& other) const { return ptr != other.ptr; }

	private:
		T* ptr;
	};

	void push_back(T value)
	{
		if (_size + 1 > capacity)
		{
			capacity = capacity * 2 + 1;
			T* new_data = new T[capacity];
			MemoryCopy(new_data, data, _size * sizeof(T));
			delete[] data;
			data = new_data;
		}
		data[_size++] = value;
	}

	T& at(size_t index)
	{
		if (index < 0 || index >= size())
			throw "ERROR: In at function: index out of bound.";
		return data[index];
	}

	bool erase(DynamicArrayListIterator& iterator)
	{
		size_t diff = iterator - begin();
		if (diff >= size())
			throw "ERROR: erase item out of bound.";

		for (int i = diff; i < size; i++)
			data[i] = data[i + 1];
		return true;
	}

	bool pop_back()
	{
		if (_size > 0)
		{
			_size--;
			return true;
		}
		return false;
	}

	void clear() {
		_size = 0;
	}

	size_t size()const {
		return _size;
	}

	DynamicArrayListIterator begin()
	{
		return data;
	}

	DynamicArrayListIterator end()
	{
		return data + _size;
	}

	T& operator[](int index)
	{
		if (index < _size && index >=0)
			return data[index];
		throw std::out_of_range("index out of range");
	}

	~DynamicArrayList()
	{
		_size = capacity = 0;
		delete[] data;
	}
private:

	T* data;

	size_t _size;

	size_t capacity;
};