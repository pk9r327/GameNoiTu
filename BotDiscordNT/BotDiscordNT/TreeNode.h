#pragma once

template <typename T> struct TreeNode
{
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
};