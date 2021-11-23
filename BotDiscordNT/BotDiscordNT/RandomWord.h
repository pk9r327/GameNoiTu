#pragma once
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "EncoderTiengViet.h"
#include <random>

class RandomWord
{
public:
	static RandomWord* getInstance()
	{
		if (!instance)
			instance = new RandomWord;
		return instance;
	}

	std::wstring getRandomStartWord()
	{
		int index = distr(eng);
		return startWords[index];
	}

private:
	int sizeStartWords;

	std::wstring* startWords;

	static RandomWord* instance;

	std::default_random_engine eng;
	std::uniform_int_distribution<int> distr;

	RandomWord()
	{
		std::wifstream rf("start_word.txt");
		rf.imbue(std::locale()); // sử dụng để đọc file Tiếng Việt

		rf >> sizeStartWords;
		rf.ignore(); // ignore \n

		std::wstring line;

		startWords = new std::wstring[sizeStartWords];
		std::getline(rf, line);
		EncoderTiengViet::splitString(line, startWords, L",");

		rf.close();

		std::random_device rd;
		eng = std::default_random_engine(rd());
		distr = std::uniform_int_distribution<int>(0, sizeStartWords - 1);
	}

};

//Initialize pointer to zero so that it can be initialized in first call to getInstance
RandomWord* RandomWord::instance = nullptr;