#pragma once
#include"MyArray.h"
#include <cstdint>
#include <fstream>
#include <string>
#include "EncoderTiengViet.h"
#include "ArrayBuilder.h"

#define SIZE_TABLE 600000

class Dictionary
{
public:
	static Dictionary* getInstance()
	{
		if (!instance)
			instance = new Dictionary;
		return instance;
	}

	bool checkMeaning(std::wstring word)
	{
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();

		std::wstring vs[2];
		EncoderTiengViet::splitString(word, vs, L" ");

		uint16_t key = encoderTiengViet->encodingWordToInt16(vs[0]);
		uint16_t x = encoderTiengViet->encodingWordToInt16(vs[1]);
		if (table[key] != nullptr && binarySearch(table[key]->arr, table[key]->size, x) != -1)
			return true;
		return false;
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

		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();

		std::wifstream rf("dictionary.txt");
		rf.imbue(std::locale()); // sử dụng để đọc file Tiếng Việt

		std::wstring line;
		std::wstring vs[2];
		uint16_t key = 0;

		uint16_t tmp = 0;

		std::getline(rf, line, L',');
		EncoderTiengViet::splitString(line, vs, L" ");
		tmp = encoderTiengViet->encodingWordToInt16(vs[0]);

		while (!rf.eof())
		{
			ArrayBuilder<uint16_t> arrayBuilder;
			while (tmp == key)
			{
				arrayBuilder.add(encoderTiengViet->encodingWordToInt16(vs[1]));

				std::getline(rf, line, L',');
				EncoderTiengViet::splitString(line, vs, L" ");
				tmp = encoderTiengViet->encodingWordToInt16(vs[0]);
			}

			table[key] = arrayBuilder.toMyArray();
			key = tmp;
		}
		
		rf.close();
	}

	int binarySearch(uint16_t arr[], int numElems, uint16_t x)
	{
		int first = 0,
			last = numElems - 1,
			middle;

		while (first <= last)
		{
			middle = (first + last) / 2;
			if (arr[middle] == x) {
				return middle;
			}
			else if (arr[middle] > x)
			{
				last = middle - 1;
			}
			else {
				first = middle + 1;
			}
		}
		return -1;  // not found
	}

private:
	MyArray<uint16_t>** table;
};

//Initialize pointer to zero so that it can be initialized in first call to getInstance
Dictionary* Dictionary::instance = nullptr;