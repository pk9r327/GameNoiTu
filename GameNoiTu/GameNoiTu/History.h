#pragma once
#include <string>
#include "Node.h"
#include "EncoderTiengViet.h"

class History
{
public:
	History()
	{
		head = nullptr;
		count = 0;
	}

	~History()
	{
		removeAll();
	}

	void removeAll()
	{
		Node<std::wstring>* node = head;

		while (node != nullptr)
		{
			Node<std::wstring>* t = node;
			node = node->link;
			delete t;
		}

		head = nullptr;
		count = 0;
	}

	bool add(std::wstring x)
	{
		if (isExists(x))
			return false;

		Node<std::wstring>* node = new Node<std::wstring>;
		node->data = x;
		node->link = head;
		head = node;
		count++;
		return true;
	}

	bool isExists(std::wstring x)
	{
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();
		Node<std::wstring>* node = head;

		if (node == nullptr) // history empty
			return false;

		while (node->link != nullptr)
		{
			if (encoderTiengViet->compareWord(node->data, x) == 0
				&& encoderTiengViet->compareWord(node->link->data, head->data) == 0)
			{
				return true;
			}
			node = node->link;
		}

		return false;
	}

	int getCount()
	{
		return count;
	}

	std::wstring getHead()
	{
		return head->data;
	}

protected:
	int count;
	Node<std::wstring>* head;
};