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
		head = nullptr;
		count = 0;
	}

	~ArrayBuilder()
	{
		Node<T>* node;
		
		// Xoá phần từ đầu tiên của danh sách đến khi rỗng
		while (head != nullptr)
		{
			node = head;
			head = node->link;
			delete node;
		}
	}

	/// <summary>
	/// Thêm một phần tử vào đầu danh sách liên kết đơn
	/// </summary>
	/// <param name="x"></param>
	void add(T x)
	{
		Node<T>* node = new Node<T>;
		node->data = x;
		node->link = head;
		head = node;
		count++;
	}

	/// <summary>
	/// Chuyển thành danh sách sử dụng mảng (con trỏ), 
	/// danh sách mảng trả về sẽ ngược với danh sách liên kết
	/// </summary>
	/// <returns></returns>
	MyArray<T>* toMyArray()
	{
		MyArray<T>* arr = new MyArray<T>(count);
		Node<T>* node = head;
		for (int i = count - 1; i >= 0; i--)
		{
			(*arr)[i] = node->data;
			node = node->link;
		}
		return arr;
	}

private:
	/// <summary>
	/// Node đầu của danh sách liên kết
	/// </summary>
	Node<T>* head;

	/// <summary>
	/// Số phần tử trong danh sách liên kết
	/// </summary>
	int count;
};

