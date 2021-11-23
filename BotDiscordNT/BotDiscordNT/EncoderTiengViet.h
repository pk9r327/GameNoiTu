#pragma once
#include <string>
#include <fstream>

// Use "Singleton design pattern"
class EncoderTiengViet
{
public:
	uint16_t encodingWordToInt16(std::wstring word)
	{
		uint16_t result = UINT16_MAX;
		int indexStart = -1, indexEnd = -1, tone = -1;
		f.tolower(&word[0], &word[0] + word.size());

		tone = removeTone(word);

		for (int i = 0; i < sizeSpecials; i++)
		{
			if (word == specials[i])
			{
				indexStart = 31;
				indexEnd = i;
				result = (indexEnd << 8) + (indexStart << 3) + tone;
				return result;
			}
		}

		std::wstring start;
		for (int i = sizeStarts - 1; i >= 0; i--)
		{
			start = starts[i];
			if (word._Starts_with(start))
			{
				indexStart = i;
				break;
			}
		}
		std::wstring end = word.substr(start.length());
		indexEnd = binarySearch(ends, sizeEnds, end);

		if (indexEnd != -1)
		{
			result = (indexEnd << 8) + (indexStart << 3) + tone;
		}

		return result;
	}

	int compareWord(std::wstring word1, std::wstring word2)
	{
		int tmp = (int)encodingWordToInt16(word1) - encodingWordToInt16(word2);
		if (tmp < 0)
			return -1;
		if (tmp == 0)
			return 0;
		return 1;
	}

	static EncoderTiengViet* getInstance()
	{
		if (!instance)
			instance = new EncoderTiengViet;
		return instance;
	}

	static void splitString(std::wstring str, std::wstring out[], std::wstring del = L" ")
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

	int sizeSpecials;
	int sizeStarts;
	int sizeEnds;
	int sizeTones;

	std::wstring* specials;
	std::wstring* starts;
	std::wstring* ends;
	std::wstring* tones;

	static EncoderTiengViet* instance;

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

	int removeTone(std::wstring& word)
	{
		int lenght = word.size();
		int tone = 0;

		for (int i = lenght - 1; i >= 0; i--)
		{
			if (word[i] >= 224)
			{
				for (int j = 0; j < sizeTones; j++)
				{
					for (int k = 1; k < 6; k++)
					{
						if (word[i] == tones[j][k])
						{
							word[i] = tones[j][0];
							tone = k;
							return tone;
						}
					}
				}
			}
		}
		return tone;
	}

	int binarySearch(std::wstring words[], int numElems, std::wstring word)
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
};

//Initialize pointer to zero so that it can be initialized in first call to getInstance
EncoderTiengViet* EncoderTiengViet::instance = nullptr;