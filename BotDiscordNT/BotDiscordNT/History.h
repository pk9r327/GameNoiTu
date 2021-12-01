#pragma once
#include "TreeNode.h" // TreeNode<uint32_t>
#include "EncoderTiengViet.h" // encodingSoundToInt16

/// <summary>
/// Lưu trữ các encode của các từ trong màn chơi theo cấu trúc cây nhị phân, các giá trị trong cây là duy nhất
/// </summary>
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

	/// <summary>
	/// Xoá tất cả các node của cây
	/// </summary>
	void removeAll()
	{
		remove(root);
		count = 0;
	}

	/// <summary>
	/// Thêm giá trị encode của x vào cây
	/// </summary>
	/// <param name="x">Giá trị cần encode và thêm vào</param>
	/// <returns>
	///		<para>true: Thêm giá trị thành công</para>
	///		<para>false: Thêm giá trị không thành công (giá trị đã tồn tại trong cây)</para>
	/// </returns>
	bool add(const std::wstring& x)
	{
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();

		uint32_t encode = encoderTiengViet->encodingWordToUInt32(x);

		TreeNode<uint32_t>** treeNode = &root;

		if ((*treeNode) == nullptr)
		{
			TreeNode<uint32_t>* T = new TreeNode<uint32_t>;
			T->data = encode;
			T->left = nullptr;
			T->right = nullptr;
			root = T;
			count++;
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

	/// <summary>
	/// Kiểm tra từ đã tồn tại trong cây trước đó
	/// </summary>
	/// <param name="encode"></param>
	/// <returns>
	///		<para>true: Giá trị đã tồn tại trong cây</para>
	///		<para>false: Giá trị chưa tồn tại trong cây</para>
	/// </returns>
	bool isExisted(const uint32_t& encode)
	{
		TreeNode<uint32_t>** treeNode = &root;

		if ((*treeNode) == nullptr)
		{
			return false;
		}

		while ((*treeNode) != nullptr)
		{
			if ((*treeNode)->data == encode)
			{
				return true;
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

		return false;
	}

	int getCount()
	{
		return count;
	}

private:
	/// <summary>
	/// Số lượng phần tử của cây nhị phân (số lượng các từ đã chơi trong màn chơi)
	/// </summary>
	int count;

	/// <summary>
	/// Gốc của cây nhị phân
	/// </summary>
	TreeNode<uint32_t>* root;

	/// <summary>
	/// Xoá tất một node của cây, các node con của cây cũng sẽ bị xoá
	/// </summary>
	/// <param name="node">NodeTree cần xoá</param>
	void remove(TreeNode<uint32_t>*& node)
	{
		if (node == nullptr)
			return;

		remove(node->left);
		remove(node->right);

		delete node;
		node = nullptr;
	}
};