#pragma once
#include <string>
#include <fstream>

class EncoderTiengViet
{
public:
	EncoderTiengViet()
	{
		std::wifstream rf("encoder.txt");
		rf.imbue(std::locale()); // sử dụng để đọc file Tiếng Việt

		std::wstring line;

		std::getline(rf, line);
		splitString(line, starts, L",");

		std::getline(rf, line);
		splitString(line, ends, L",");

		for (int i = 0; i < SIZE_TONES; i++)
		{
			std::getline(rf, line);
			tones[i] = line;
		}

		rf.close();
	}

	uint16_t encodingWordToInt16(std::wstring word)
	{
		int indexStart = -1, indexEnd = -1, tone = -1;
		f.tolower(&word[0], &word[0] + word.size());

		tone = removeTone(word);

		std::wstring start;
		for (int i = SIZE_STARTS - 1; i >= 0; i--)
		{
			start = starts[i];
			// Check string start with
			if (word.compare(0, start.length(), start) == 0)
			{
				indexStart = i;
				break;
			}
		}
		std::wstring end = word.substr(start.length());
		indexEnd = binarySearch(ends, SIZE_ENDS, end);

		uint16_t result = (indexEnd << 8) + (indexStart << 3) + tone;
		return result;
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
	static constexpr int SIZE_STARTS = 28;
	static constexpr int SIZE_ENDS = 135;
	static constexpr int SIZE_TONES = 12;

	// Sử dụng để xử lý chuỗi Tiếng Việt
	const std::ctype<wchar_t>& f = std::use_facet<std::ctype<wchar_t>>(std::locale());

	std::wstring starts[SIZE_STARTS];
	std::wstring ends[SIZE_ENDS];
	std::wstring tones[SIZE_TONES];

	int removeTone(std::wstring& word)
	{
		int lenght = word.size();
		int tone = 0;

		for (int i = 0; i < lenght; i++)
		{
			if (word[i] >= 224)
			{
				for (int j = 0; j < 12; j++)
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
		int first = 0,                 //first array element
			last = numElems - 1,            //last array element
			middle;                        //mid point of search

		while (first <= last)
		{
			middle = (first + last) / 2; //this finds the mid point
			if (words[middle] == word) {
				return middle;
			}
			else if (words[middle] > word) // if it's in the lower half
			{
				last = middle - 1;
			}
			else {
				first = middle + 1;                 //if it's in the upper half
			}
		}
		return -1;  // not found
	}
};