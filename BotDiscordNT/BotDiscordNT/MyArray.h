#pragma once

/// <summary>
/// Danh sách sử dụng mảng đơn giản có kích thước của mảng
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
class MyArray
{
public:
	MyArray(const int& size_)
	{
		size = size_;
		arr = new T[size];
	}

	~MyArray()
	{
		delete[] arr;
	}

	/// <summary>
	/// Truy cập đến một phần tử của mảng
	/// </summary>
	/// <param name="index">Thứ tự của phần tử trong mảng</param>
	/// <returns></returns>
	T& operator[](const int& index)
	{
		return arr[index];
	}

	int size;
	T* arr;
};