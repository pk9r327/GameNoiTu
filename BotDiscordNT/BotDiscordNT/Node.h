#pragma once

/// <summary>
/// Nút sử dụng cho danh sách liên kết đơn
/// </summary>
/// <typeparam name="T">Tên kiểu dữ liệu của Node</typeparam>
template <typename T> struct Node
{
	/// <summary>
	/// Giá trị của Node
	/// </summary>
	T data;

	/// <summary>
	/// Liên kết của Node
	/// </summary>
	Node<T>* link;
};