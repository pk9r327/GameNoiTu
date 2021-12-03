#pragma once
#include "Node.h" // Node<T>
#include "MyArray.h" // MyArray<T>

/// <summary>
/// Tạo mảng bằng danh sách liên kết đơn có thể chuyển qua danh sách sủ dụng mảng
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T>
class ArrayBuilder
{
public:

	ArrayBuilder()
	{
		tail = nullptr;
		count = 0;
	}

	~ArrayBuilder()
	{
		Node<T>* node;
		
		// Xoá phần từ cuối cùng của danh sách đến khi rỗng
		while (tail != nullptr)
		{
			node = tail;
			tail = node->link;
			delete node;
		}
	}

	/// <summary>
	/// Thêm một phần tử vào cuối danh sách liên kết đơn
	/// </summary>
	/// <param name="x"></param>
	void add(T x)
	{
		Node<T>* node = new Node<T>;
		node->data = x;
		node->link = tail;
		tail = node;
		count++;
	}

	/// <summary>
	/// Chuyển thành danh sách sử dụng mảng (con trỏ)
	/// </summary>
	/// <returns></returns>
	MyArray<T>* toMyArray()
	{
		MyArray<T>* arr = new MyArray<T>(count);
		Node<T>* node = tail;
		for (int i = count - 1; i >= 0; i--)
		{
			(*arr)[i] = node->data;
			node = node->link;
		}
		return arr;
	}

private:
	/// <summary>
	/// Node cuối của danh sách liên kết
	/// </summary>
	Node<T>* tail;

	/// <summary>
	/// Số phần tử trong danh sách liên kết
	/// </summary>
	int count;
};

