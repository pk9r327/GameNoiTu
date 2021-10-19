#pragma once
#include <string>
#include <codecvt> // codecvt_utf8
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
		// Sử dụng mã hoá UTF-8 để đọc tệp tiếng việt
		std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);

		std::wifstream rf("dic.txt");
		rf.imbue(loc);

		rf.close();

		resetGame();
		// Chưa hoàn thành
	}

	ErrorAddWord addWord(std::wstring word)
	{
		std::wstring vs[2];
		splitString(word, vs);

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

private:
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
};