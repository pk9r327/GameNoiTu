#pragma once
#include <string>
#include "Node.h"
#include "EncoderTiengViet.h"

/* Task: Tạo cấu trúc dữ liệu để lưu trữ các từ được sử dụng trong màn chơi (sử dụng liên kết đơn)
* Ví dụ: ['động'->'tác'->'động'->'khởi'] => khởi động, động tác, tác động
* Note: tác động và động tác là 2 từ khác nhau nên vẫn tính
*/

/* bool add(std::wstring): thêm một từ vào đầu danh sách
* 
* Trả về true khi từ được thêm vào danh sách
* Ví dụ: ['tác'->'động'->'khởi']; add(L"động") => ['động'->'tác'->'động'->'khởi'] { return true; }
* 
* Trả về false khi từ thêm vào đã xuất hiện trong danh sách
* Ví dụ: ['động'->'tác'->'động'->'khởi']; add(L"tác") => ['động'->'tác'->'động'->'khởi'] { return false; }
*/

/* bool isContain(std::wstring): kiểm tra từ chuẩn bị thêm vào có trong danh sách chưa
* Làm để add(std::wstring) sử dụng lại nhìn cho gọn code
*/

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
		count = 0;
	}

	bool add(std::wstring x)
	{
		Node<std::wstring>* node = new Node<std::wstring>;
		node->data = x;
		node->link = head;
		head = node;
		count++;
		return true;
	}

	bool isContain(std::wstring x)
	{
		// so sánh từ giống nhau (encoderTiengViet->compareWord(a, b) == 0)
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();

		Node<std::wstring>* node = head;



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