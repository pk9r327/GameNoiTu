#pragma once
#include "Node.h"
#include "MyArray.h"

template <typename T>
class ArrayListBuilder
{
public:

	ArrayListBuilder()
	{
		head = nullptr;
		count = 0;
	}

	void add(T x)
	{
		Node<T>* node = new Node<T>;
		node->data = x;
		node->link = head;
		head = node;
		count++;
	}

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
	Node<T>* head;
	int count;
};

