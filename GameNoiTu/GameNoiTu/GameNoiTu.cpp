#include <iostream>
#include <tuple> // std::ignore
#include <corecrt_io.h> // _setmode
#include <fcntl.h> // _O_U8TEXT
#include "GameNoiTu.h"
#include "GameManagement.h"

int main()
{
	/* Note: chuỗi tiếng việt là mã hoá UTF-8,
	ta cần sử dụng các kiểu dữ liệu, hàm phù hợp với mã hoá này như
	wchar_t, std::wstring, std::wcout, wprintf, ... (thường sẽ có chữ w)
	Chuỗi mã hoá Unicode sẽ bắt đâu bằng tiền tố L. Ví dụ: L"Unícódé" */

	// Sử dụng input, output tiếng việt
	std::ignore = _setmode(_fileno(stdout), _O_U8TEXT);
	std::ignore = _setmode(_fileno(stdin), _O_U8TEXT);

	int player = 1;
	std::wstring input;

	GameManagement game_management;
	std::wstring start_word;

	for (;;)
	{
		start_word = game_management.get_start_word();
		bool is_valid = false;
		while (!is_valid)
		{
			wprintf(L"Lượt của người chơi %d: %s ", player, start_word.c_str());
			std::getline(std::wcin, input);

			if (input == L"give up")
			{
				change_turns(player);
				wprintf(L"Trò chơi kết thúc người chơi %d thắng!\n", player);
				game_management.reset_game();
				break;
			}

			is_valid = game_management.add_word(input);
			if (!is_valid)
			{
				wprintf(L"'%s %s' không có nghĩa, vui lòng thử từ khác!\n",
					start_word.c_str(), input.c_str());
			}
		}
		
		change_turns(player);
	}
}

void change_turns(int& player)
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