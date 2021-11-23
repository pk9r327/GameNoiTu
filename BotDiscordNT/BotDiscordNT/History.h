#pragma once
#include <string>
#include "TreeNode.h"
#include "EncoderTiengViet.h"

class History
{
public:
	History()
	{
		root = nullptr;
		count = 0;
	}

	~History()
	{
		removeAll();
	}

	void removeAll()
	{
		removeAll(root);
	}

	bool add(std::wstring x)
	{
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();
		std::wstring vs[2];
		EncoderTiengViet::splitString(x, vs);

		uint16_t encode1 = encoderTiengViet->encodingWordToInt16(vs[0]);
		uint16_t encode2 = encoderTiengViet->encodingWordToInt16(vs[1]);

		uint32_t encode = (uint32_t)encode1 << 16 + encode2;

		TreeNode<uint32_t>** treeNode = &root;

		if ((*treeNode) == nullptr)
		{
			TreeNode<uint32_t>* T = new TreeNode<uint32_t>;
			T->data = encode;
			T->left = nullptr;
			T->right = nullptr;
			root = T;
			return true;
		}

		while ((*treeNode) != nullptr)
		{
			if ((*treeNode)->data == encode)
			{
				return false;
			}

			if ((*treeNode)->data < encode)
			{
				treeNode = &((*treeNode)->left);
			}
			else
			{
				treeNode = &((*treeNode)->right);
			}
		}

		(*treeNode) = new TreeNode<uint32_t>;
		(*treeNode)->data = encode;
		(*treeNode)->left = nullptr;
		(*treeNode)->right = nullptr;
		count++;
		return true;
	}

	int getCount()
	{
		return count;
	}

protected:
	int count;
	TreeNode<uint32_t>* root;

	void removeAll(TreeNode<uint32_t>*& node)
	{
		if (node == nullptr)
			return;

		removeAll(node->left);
		removeAll(node->right);

		delete node;
		node = nullptr;
	}
};