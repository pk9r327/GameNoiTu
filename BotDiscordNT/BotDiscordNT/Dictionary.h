#pragma once
#include"MyArray.h"
#include <cstdint>

#define SIZE_TABLE 600000

class Dictionary
{
public:
	Dictionary()
	{
		table = new MyArray<uint16_t>*[SIZE_TABLE];
		for (int i = 0; i < SIZE_TABLE; i++)
		{
			table[i] = nullptr;
		}


	}

private:
	MyArray<uint16_t>** table;
};

