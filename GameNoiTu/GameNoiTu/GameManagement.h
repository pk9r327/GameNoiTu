#pragma once
#include <string>
#include <fstream>
#include "History.h"

enum class ErrorAddWord
{
	None, InvalidStart, Exists, NoMeaning
};

class GameManagement
{

public:
	GameManagement()
	{
		std::wifstream rf("dic.txt");
		rf.imbue(std::locale()); // sử dụng để đọc file Tiếng Việt

		rf.close();

		resetGame();
		// Chưa hoàn thành
	}

	ErrorAddWord addWord(std::wstring word)
	{
		std::wstring vs[2];
		EncoderTiengViet::splitString(word, vs);

		if (vs[0] != currentWord)
		{
			return ErrorAddWord::InvalidStart;
		}

		if (history.isContain(word))
		{
			return ErrorAddWord::Exists;
		}

		currentWord = vs[1];
		history.add(word);
		return ErrorAddWord::None;
		// Chưa hoàn thành
	}

	void resetGame()
	{
		history.removeAll();

		currentWord = getStartWord();

		// Chưa hoàn thành
	}

	std::wstring getStartWord()
	{
		return L"khởi";
		// Chưa hoàn thành
	}

	std::wstring getCurrentWord()
	{
		return currentWord;
	}

protected:

	History history;
	std::wstring currentWord;
};