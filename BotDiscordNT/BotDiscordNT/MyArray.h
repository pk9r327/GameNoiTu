#pragma once

/// <summary>
/// Danh sách sử dụng mảng đơn giản có kích thước của mảng
/// </summary>
/// <typeparam name="T"></typeparam>
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