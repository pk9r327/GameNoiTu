#pragma once
#include <string>
#include <fstream>

// Use "Singleton design pattern"
class EncoderTiengViet
{
public:

	/// <summary>
	/// Mã hoá một âm của tiếng việt thành một số uint16_t
	/// </summary>
	/// <param name="sound">Âm cần mã hoá</param>
	/// <returns>
	///		<para>Giá trị mã hoá trong đoạn [0, 38877] (mã hoá thành công)</para>
	///		<para>UINT16_MAX = 0xffffui16 (mã hoá thất bại, âm không hợp lệ)</para>
	/// </returns>
	uint16_t encodingSoundToUInt16(std::wstring sound)
	{
		uint16_t result = UINT16_MAX;
		int indexStart = -1, indexEnd = -1, tone = -1;

		// Chuyển tất cả thành chữ thường để so sánh
		f.tolower(&sound[0], &sound[0] + sound.size());

		tone = removeTone(sound);

		//for (int i = 0; i < sizeSpecials; i++)
		//{
		//	if (sound == specials[i])
		//	{
		//		indexStart = 31;
		//		indexEnd = i;
		//		result = (indexEnd << 8) + (indexStart << 3) + tone;
		//		return result;
		//	}
		//}

		indexEnd = binarySearch(specials, sizeSpecials, sound);
		if (indexEnd != -1)
		{
			indexStart = 31;
			result = (indexEnd << 8) + (indexStart << 3) + tone;
			return result;
		}

		std::wstring start;
		for (int i = sizeStarts - 1; i >= 0; i--)
		{
			start = starts[i];
			if (sound._Starts_with(start))
			{
				indexStart = i;
				break;
			}
		}
		std::wstring end = sound.substr(start.length());
		indexEnd = binarySearch(ends, sizeEnds, end);

		if (indexEnd != -1)
		{
			result = (indexEnd << 8) + (indexStart << 3) + tone;
		}

		return result;
	}
	
	/// <summary>
	/// Mã hoá một từ có 2 âm tiết thành một số uint32_t
	/// </summary>
	/// <param name="word">Từ cần mã hoá</param>
	/// <returns>Giá trị mã hoá</returns>
	uint32_t encodingWordToUInt32(const std::wstring& word)
	{
		std::wstring sounds[2];
		splitString(word, sounds);

		uint16_t encode1 = encodingSoundToUInt16(sounds[0]);
		uint16_t encode2 = encodingSoundToUInt16(sounds[1]);

		return (uint32_t)encode1 << 16 + encode2;
	}

	/// <summary>
	/// Kiểm tra 2 âm có giống nhau không
	/// </summary>
	/// <param name="sound1">Âm thứ nhất</param>
	/// <param name="sound2">Âm thứ hai</param>
	/// <returns></returns>
	bool isEquals(const std::wstring& sound1, const std::wstring& sound2)
	{
		return encodingSoundToUInt16(sound1) == encodingSoundToUInt16(sound2);
	}

	/// <summary>
	/// Singleton Instance 
	/// (đối tượng EncoderTiengViet duy nhất trong suốt quá trình chạy của chương trình)
	/// </summary>
	/// <returns></returns>
	static EncoderTiengViet* getInstance()
	{
		if (!instance)
			instance = new EncoderTiengViet;
		return instance;
	}

	/// <summary>
	/// Tách chuỗi thành mảng
	/// </summary>
	/// <param name="str">Chuỗi cần tách</param>
	/// <param name="out">Mảng xuất ra sau khi tách</param>
	/// <param name="del">Chuỗi ngăn cách</param>
	static void splitString(const std::wstring& str, std::wstring out[],
		const std::wstring& del = L" ")
	{
		int start = 0;
		int end = str.find(del);
		int index = 0;
		while (end != -1) {
			out[index++] = str.substr(start, end - start);
			start = end + del.size();
			end = str.find(del, start);
		}
		out[index++] = str.substr(start, end - start);
	}

private:
	// Sử dụng để xử lý chuỗi Tiếng Việt
	const std::ctype<wchar_t>& f = std::use_facet<std::ctype<wchar_t>>(std::locale());

#pragma region SizeArray
	/// <summary>
	/// Số lượng các âm đặc biệt của tiếng việt
	/// </summary>
	int sizeSpecials;

	/// <summary>
	/// Số lượng các chuỗi bắt đầu của âm tiếng việt
	/// </summary>
	int sizeStarts;

	/// <summary>
	/// Số lượng các chuỗi kết thúc của âm tiếng việt
	/// </summary>
	int sizeEnds;

	/// <summary>
	/// Số lượng các chuỗi chứa các ký tự có dấu trong tiếng việt
	/// </summary>
	int sizeTones;
#pragma endregion

#pragma region Array
	/// <summary>
	/// Mảng các âm đặc biệt của tiếng việt
	/// </summary>
	std::wstring* specials;

	/// <summary>
	/// Mảng các chuỗi bắt đầu của âm tiếng việt
	/// </summary>
	std::wstring* starts;

	/// <summary>
	/// Mảng các chuỗi kết thúc của âm tiếng việt
	/// </summary>
	std::wstring* ends;

	/// <summary>
	/// Mảng các chuỗi chứa các ký tự có dấu trong tiếng việt
	/// </summary>
	std::wstring* tones;
#pragma endregion

	// Private constructor so that no objects can be created. (Singleton design pattern)
	EncoderTiengViet()
	{
		std::wifstream rf("encoder.txt");
		rf.imbue(std::locale()); // sử dụng để đọc file Tiếng Việt

		rf >> sizeSpecials >> sizeStarts >> sizeEnds >> sizeTones;
		rf.ignore(); // ignore \n

		specials = new std::wstring[sizeSpecials];
		starts = new std::wstring[sizeStarts];
		ends = new std::wstring[sizeEnds];
		tones = new std::wstring[sizeTones];

		std::wstring line;

		std::getline(rf, line);
		splitString(line, specials, L",");

		std::getline(rf, line);
		splitString(line, starts, L",");

		std::getline(rf, line);
		splitString(line, ends, L",");

		std::getline(rf, line);
		splitString(line, tones, L",");

		rf.close();

		//dictionary = new Dictionary();
	}

	/// <summary>
	/// Tách dấu của một âm tiếng việt
	/// </summary>
	/// <param name="sound">Âm cần tách dấu, sau khi tách sẽ mất dấu</param>
	/// <returns>Giá trị của dấu</returns>
	int removeTone(std::wstring& sound)
	{
		int lenght = sound.size();
		int tone = 0;

		for (int i = lenght - 1; i >= 0; i--)
		{
			if (sound[i] >= 224) // Giá trị bé nhất của một kí tự có dấu
			{
				for (int j = 0; j < sizeTones; j++)
				{
					for (int k = 1; k < 6; k++) // Duyệt các kí tự có dấu (trừ dấu thanh)
					{
						if (sound[i] == tones[j][k])
						{
							sound[i] = tones[j][0];
							tone = k;
							return tone;
						}
					}
				}
			}
		}
		return tone;
	}

	/// <summary>
	/// Tìm kiếm nhị phân của mảng chuỗi đã được sắp xếp tăng dần
	/// </summary>
	/// <param name="words">Mảng chuỗi đã được sắp xếp tăng dần</param>
	/// <param name="numElems">Số lượng phần từ của mảng</param>
	/// <param name="word">Giá trị cần tìm kiếm</param>
	/// <returns>
	///		<para>Vị trí của phần tử trong mảng (tìm thấy)</para>
	///		<para>Giá trị -1 (không tìm thấy)</para>
	/// </returns>
	int binarySearch(std::wstring words[], const int& numElems, const std::wstring& word)
	{
		int first = 0,
			last = numElems - 1,
			middle;

		while (first <= last)
		{
			middle = (first + last) / 2;
			if (words[middle] == word) {
				return middle;
			}
			else if (words[middle] > word)
			{
				last = middle - 1;
			}
			else {
				first = middle + 1;
			}
		}
		return -1;  // not found
	}

	static EncoderTiengViet* instance;
};

//Initialize pointer to zero so that it can be initialized in first call to getInstance
EncoderTiengViet* EncoderTiengViet::instance = nullptr;