#pragma once
template <typename T>
class MyArray
{
public:
	MyArray(int size_)
	{
		size = size_;
		arr = new T[size];
	}

	~MyArray()
	{
		delete[] arr;
	}


	T& operator[](int index)
	{
		return arr[index];
	}

	int size;
	T* arr;
};