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

		if (history.isExists(vs[1])==true)
		{
			return ErrorAddWord::Exists;
		}

		currentWord = vs[1];
		history.add(vs[1]);
		return ErrorAddWord::None;
		// Chưa hoàn thành
	}

	void resetGame()
	{
		currentWord = getStartWord();

		history.removeAll();
		history.add(currentWord);
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