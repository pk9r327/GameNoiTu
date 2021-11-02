#pragma once
#include <string>
#include <fstream>
#include <cstdlib>
#include <limits>
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
		system("CLS");

		getStartWord(currentWord);

		history.removeAll();
		history.add(currentWord);
		// Chưa hoàn thành
	}

	void getStartWord(std::wstring& startword)
	{
		wprintf(L"Vui lòng chọn chế độ\n");
		wprintf(L"Nhấn [1] để chọn ngẫu nhiên 1 từ khởi đầu\n");
		wprintf(L"Nhấn [2] để nhập tay từ khởi đầu bạn chọn\n");
		wprintf(L"-------------------------------------------\n");
		std::wstring choice;
	enterChoice:
		wprintf(L"Bạn muốn chọn chế độ nào : ");
		std::getline(std::wcin, choice);
		if (choice != L"1" && choice != L"2")
		{
			wprintf(L"Lựa chọn không hợp lệ\n");
			goto enterChoice;
		}

		switch (stoi(choice))
		{
		case 1:
		{
			startword = getStartWordRandomly();
			break;
		}
		case 2:
		{
			startword = getStartWordManually();
			break;
		}
		}
	}

	std::wstring getStartWordRandomly()
	{
		std::wstring FirstWord,Numoftext;
		//StartWords.txt
		//Mở file
		std::wifstream st("StartWords.txt");
		if (st.fail())
		{
			std::cout << "Failed to open the Start file" << std::endl;
			return L"";
		}

		//Lấy random dòng trong 497 dòng
		st.imbue(std::locale());
		srand((unsigned)time(NULL));
		wchar_t WordArray[30];
		// range = 497 
		int randomLine = 1 + (rand() % 497);

		//wprintf(L"Random line = %d\n\n", randomLine);

		std::ios_base::sync_with_stdio(false);
		st.seekg(0);
		// Chuyển tới dòng cần dùng
		for (int i = 0; i < randomLine - 1; ++i)
			st.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// Lấy số lượng từ trong 1 dòng
		st.getline(WordArray, sizeof(WordArray), ',');
		Numoftext = WordArray;

		//std::wcout << L"Num of text in line = " << Numoftext << L"\n\n";

		// Lấy 1 từ bất kì trong dòng đó
		for (int i = 1; i <= 1 + (rand() % stoi(Numoftext)); i++)
		{
			st.getline(WordArray, sizeof(WordArray), ',');
		}

		FirstWord = WordArray;
		st.close();

		// yeah, it works
		// nhưng có vẻ chưa tối ưu lắm chỗ đọc random
		// mình tính làm vầy : Khởi đầu trò chơi sẽ cho chọn 2 chế độ
		// 1 - Tự điền từ bắt đầu
		// 2 - Lấy random 

		return FirstWord;
	}

	std::wstring getStartWordManually()
	{
		std::wstring FirstWord;
		wprintf(L"Vui lòng nhập từ được chọn để bắt đầu trò chơi : ");
		std::getline(std::wcin, FirstWord);
		return FirstWord;
	}

	std::wstring getCurrentWord()
	{
		return currentWord;
	}

protected:

	History history;
	std::wstring currentWord;
};