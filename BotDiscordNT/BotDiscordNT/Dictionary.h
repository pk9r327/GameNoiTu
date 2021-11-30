#pragma once
#include "EncoderTiengViet.h" // encodingSoundToInt16
#include "ArrayBuilder.h" // ArrayBuilder<uint16_t>, MyArray<uint16_t>

/// <summary>
/// Số lượng phần từ của bảng băm
/// </summary>
constexpr auto SIZE_TABLE = 40000;

/// <summary>
/// Sử dụng dữ liệu từ tệp từ điển, kiểm tra tính có nghĩa của từ bằng bảng băm
/// </summary>
class Dictionary
{
public:

	/// <summary>
	/// Singleton Instance 
	/// (đối tượng Dictionary duy nhất trong suốt quá trình chạy của chương trình)
	/// </summary>
	/// <returns></returns>
	static Dictionary* getInstance()
	{
		if (!instance)
			instance = new Dictionary;
		return instance;
	}

	/// <summary>
	/// Kiểm tra tính có nghĩa của một từ có 2 âm tiết
	/// </summary>
	/// <param name="word">Từ cần kiểm tra tính có nghĩa</param>
	/// <returns>
	///		<para>true:  Từ có nghĩa</para>
	///		<para>false: Từ vô nghĩa (Từ không có nghĩa)</para>
	/// </returns>
	bool checkMeaning(const std::wstring& word)
	{
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();

		std::wstring vs[2];
		EncoderTiengViet::splitString(word, vs, L" ");

		uint16_t key = encoderTiengViet->encodingSoundToInt16(vs[0]);
		uint16_t x = encoderTiengViet->encodingSoundToInt16(vs[1]);
		if (table[key] != nullptr && binarySearch(table[key]->arr, table[key]->getSize(), x) != -1)
			return true;
		return false;
	}

	/// <summary>
	/// Lấy danh sách mảng các encode của âm kết thúc
	/// </summary>
	/// <param name="index">Mã băm của âm bắt đầu</param>
	/// <returns></returns>
	MyArray<uint16_t>* getLastSounds(const int& index)
	{
		return table[index];
	}

private:
	static Dictionary* instance;

	Dictionary()
	{
		table = new MyArray<uint16_t>*[SIZE_TABLE];
		for (int i = 0; i < SIZE_TABLE; i++)
		{
			table[i] = nullptr;
		}

		// Sử dụng Instance EncoderTiengViet
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();

		std::wifstream rf("dictionary.txt");
		rf.imbue(std::locale()); // sử dụng để đọc file Tiếng Việt

		std::wstring line;
		std::wstring vs[2];
		int key = 0;
		int tmp = 0;

		/// Đọc dữ liệu từ tệp
		std::getline(rf, line, L',');
		EncoderTiengViet::splitString(line, vs, L" ");
		tmp = hashFunction(vs[0]);

		while (!rf.eof())
		{
			ArrayBuilder<uint16_t> arrayBuilder;
			while (tmp == key)
			{
				arrayBuilder.add(encoderTiengViet->encodingSoundToInt16(vs[1]));

				std::getline(rf, line, L',');
				EncoderTiengViet::splitString(line, vs, L" ");
				tmp = hashFunction(vs[0]);
			}

			table[key] = arrayBuilder.toMyArray();
			key = tmp;
		}

		rf.close();
	}

	/// <summary>
	///		Tìm kiếm nhị phân trong mảng uint16_t đã được sắp xếp tăng dần
	/// </summary>
	/// 
	///	<param name="arr">mảng uint16_t đã được sắp xếp tăng dần</param>
	///	<param name="numElems">Số lượng phần từ của mảng</param>
	///	<param name="x">Giá trị cần tìm kiếm</param>
	/// 
	/// <returns>
	///		<para>Vị trí của phần tử trong mảng (tìm thấy)</para>
	///		<para>Giá trị -1 (không tìm thấy)</para>
	/// </returns>
	int binarySearch(uint16_t arr[], int numElems, uint16_t value)
	{
		int first = 0,
			last = numElems - 1,
			middle;

		while (first <= last)
		{
			middle = (first + last) / 2;
			if (arr[middle] == value) {
				return middle;
			}
			else if (arr[middle] > value)
			{
				last = middle - 1;
			}
			else {
				first = middle + 1;
			}
		}
		return -1;  // not found
	}

	/// <summary>
	///		<para>Buckets của bảng băm</para>
	///		<para>Là một mảng chứa các con trỏ của một mảng uint16_t</para>
	/// </summary>
	MyArray<uint16_t>** table;

	/// <summary>
	///		<para>Hàm băm của bảng băm, chuyển một âm thành int</para>
	///		<para>Là hàm băm hoàn hảo, không có va chạm</para>
	/// </summary>
	/// <param name="sound">Âm thanh cần băm</param>
	/// <returns>Giá trị băm</returns>
	int hashFunction(const std::wstring& sound)
	{
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();
		return encoderTiengViet->encodingSoundToInt16(sound);
	}
};

//Initialize pointer to zero so that it can be initialized in first call to getInstance
Dictionary* Dictionary::instance = nullptr;