#include <iostream>
#include <tuple> // std::ignore
#include <corecrt_io.h> // _setmode
#include <fcntl.h> // _O_WTEXT
#include "GameNoiTu.h"
#include "GameManagement.h"

int main()
{
	/* Note: chuỗi tiếng việt là mã hoá UTF-8,
	ta cần sử dụng các kiểu dữ liệu, hàm phù hợp với mã hoá này như
	wchar_t, std::wstring, std::wcout, wprintf, ... (thường sẽ có chữ w)
	Chuỗi mã hoá Unicode sẽ bắt đâu bằng tiền tố L. Ví dụ: L"Unícódé" */

	// Sử dụng input, output tiếng việt
	std::ignore = _setmode(_fileno(stdout), _O_WTEXT);
	std::ignore = _setmode(_fileno(stdin), _O_WTEXT);

	// Sử dụng để đọc file, xử lý chuỗi tiếng việt
	std::locale::global(std::locale("en_US.UTF8"));

	int player = 1;
	std::wstring input;

	GameManagement gameManagement;
	std::wstring currentWord;

	for (;;)
	{
		currentWord = gameManagement.getCurrentWord();
		ErrorAddWord errorAddWord = ErrorAddWord::NoMeaning;
		while (errorAddWord != ErrorAddWord::None)
		{
			wprintf(L"Lượt của người chơi %d: ", player);
			// Tự động điền từ đầu tiên cho người chơi
			wprintf(L"%s ", currentWord.c_str());

			std::getline(std::wcin, input);

			if (input == L"give up")
			{
				changeTurns(player);
				wprintf(L"Trò chơi kết thúc người chơi %d thắng!\n", player);
				gameManagement.resetGame();
				break;
			}

			wchar_t word[15];
			swprintf_s(word, 15, L"%s %s", currentWord.c_str(), input.c_str());

			errorAddWord = gameManagement.addWord(word);
			switch (errorAddWord)
			{
			case ErrorAddWord::None:
				changeTurns(player);
				break;

			case ErrorAddWord::InvalidStart:
				wprintf(L"'%s' không bắt đầu bằng '%s', vui lòng thử từ khác!\n", word, currentWord.c_str());
				break;

			case ErrorAddWord::Exists:
				wprintf(L"'%s' đã được sử dụng, vui lòng thử từ khác!\n", word);
				break;

			case ErrorAddWord::NoMeaning:
				wprintf(L"'%s' không có nghĩa, vui lòng thử từ khác!\n", word);
				break;

			default:
				break;
			}
		}
	}
}

void changeTurns(int& player)
{
	if (player == 1)
	{
		player = 2;
	}
	else
	{
		player = 1;
	}
}