#pragma once
#include <string>
#include <fstream>
#include "History.h"

enum class ErrorAddWord
{
	None, InvalidPlayer, InvalidCountWord, CanNotRead, InvalidStart, Existed, NoMeaning
};

class GameManagement
{

public:
	GameManagement()
	{
		std::wifstream rf("dictionary.txt");
		rf.imbue(std::locale()); // sử dụng để đọc file Tiếng Việt

		rf.close();		

		resetGame();
		// Chưa hoàn thành
	}

	ErrorAddWord addWord(std::wstring word, uint16_t idPlayer)
	{
		if (idPlayer == lastIdPlayer)
			return ErrorAddWord::InvalidPlayer;

		if (std::count(word.begin(), word.end(), L' ') != 1)
			return ErrorAddWord::InvalidCountWord;

		std::wstring vs[2];
		EncoderTiengViet::splitString(word, vs);
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();

		if (encoderTiengViet->compareWord(vs[0], currentWord) != 0)
		{
			return ErrorAddWord::InvalidStart;
		}

		uint16_t encoded = encoderTiengViet->encodingWordToInt16(vs[1]);
		if (encoded == UINT16_MAX)
		{
			return ErrorAddWord::CanNotRead;
		}

		if (history.isExists(vs[1]))
		{
			return ErrorAddWord::Existed;
		}

		currentWord = vs[1];
		lastIdPlayer = idPlayer;
		history.add(vs[1]);
		return ErrorAddWord::None;
	}

	void resetGame()
	{
		currentWord = getStartWord();
		history.removeAll();
		history.add(currentWord);
		// Chưa hoàn thành
	}

	bool resetGame(std::wstring startWord)
	{
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();
		uint16_t encoded = encoderTiengViet->encodingWordToInt16(startWord);
		if (encoded == UINT16_MAX)
		{
			return false;
		}

		currentWord = startWord;
		history.removeAll();
		history.add(currentWord);
		return true;
	}

	std::wstring getStartWord()
	{
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();
		return encoderTiengViet->getRandomStartWord();
	}

	std::wstring getCurrentWord()
	{
		return currentWord;
	}

protected:

	History history;
	std::wstring currentWord;
	uint64_t lastIdPlayer;
};