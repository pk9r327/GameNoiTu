#pragma once
#include <string>
#include "Node.h"

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

	void add(std::wstring x)
	{
		Node<std::wstring>* node = new Node<std::wstring>;
		node->data = x;
		node->link = head;
		head = node;
		count++;
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
		count = 0;
	}

	bool isContain(std::wstring x)
	{
		Node<std::wstring>* node = head;

		while (node != nullptr)
		{
			if (node->data == x)
				return true;

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