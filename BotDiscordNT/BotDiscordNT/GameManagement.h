#pragma once
#include <string>
#include <fstream>
#include "History.h"
#include "Dictionary.h"
#include "RandomWord.h"

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
		/*if (idPlayer == lastIdPlayer)
			return ErrorAddWord::InvalidPlayer;*/

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

		Dictionary* dictionary = dictionary->getInstance();

		/*if (!dictionary->checkMeaning(word))
		{
			return ErrorAddWord::NoMeaning;
		}*/

		bool isAddSuccessed = history.add(word);
		if (isAddSuccessed)
		{
			currentWord = vs[1];
			lastIdPlayer = idPlayer;
			return ErrorAddWord::None;
		}
		else
		{
			return ErrorAddWord::Existed;
		}
	}

	void resetGame()
	{
		currentWord = getStartWord();
		history.removeAll();
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
		return true;
	}

	std::wstring getStartWord()
	{
		RandomWord* randomWord = randomWord->getInstance();
		return randomWord->getRandomStartWord();
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