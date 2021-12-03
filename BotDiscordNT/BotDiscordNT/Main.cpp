#include "Main.h"
#include "Dictionary.h"
#include <cstdarg>

int main()
{
	/* Note: chuỗi tiếng việt là mã hoá UTF-8,
	ta cần sử dụng các kiểu dữ liệu, hàm phù hợp với mã hoá này như
	wchar_t, std::wstring, std::wcout, wprintf, ... (thường sẽ có chữ w)
	Chuỗi mã hoá Unicode sẽ bắt đâu bằng tiền tố L. Ví dụ: L"Unícódé" */
	// Sử dụng input, output tiếng việt

	config();

	static GameManagement gameManagement;

	dpp::cluster bot(token);

	bot.on_ready([&bot](const dpp::ready_t& event) { // khi kết nối tới bot thành công
		std::string welcome = getString(REPLY_WELCOME);;
		bot.message_create(dpp::message(idChannel, welcome));

		std::wstring currentSound = gameManagement.getCurrentSound();
		int turn = gameManagement.history.getCount() + 1;
		std::string reply = getString(REPLY_COMMAND_INFO, currentSound.c_str(), turn);
		bot.message_create(dpp::message(idChannel, reply));

		printTimeOS();
		std::wcout << LOG_WELCOME1 << bot.me.username.c_str() << LOG_WELCOME2;
		});

	bot.on_message_create([&bot](const dpp::message_create_t& event) { // khi bot nhận tin nhắn
		performCommand(gameManagement, bot, event);
		});
	bot.start(false);
}

void performCommand(GameManagement& gameManagement, dpp::cluster& bot, const dpp::message_create_t& event)
{
	// Kiểm tra channel nhận chat
	if (event.msg->channel_id != idChannel)
		return;

	// Bỏ qua lời nhắn từ bot
	if (event.msg->author->id == bot.me.id)
		return;

	// Nội dung của tin nhắn
	std::wstring content = (std::wstring)CA2WEX(event.msg->content.c_str(), CP_UTF8);

	// Id của tin nhắn
	dpp::snowflake idContent = event.msg->id;

	// Người gửi tin nhắn
	dpp::user* author = event.msg->author;

	// Âm bắt đầu hiện tại
	std::wstring currentSound = gameManagement.getCurrentSound();


	if (content._Starts_with(COMMAND_SET)) {
		std::wstring startSound = content.substr(LENGTH_COMMAND_SET);
		if (gameManagement.resetGame(startSound))
		{
			std::string reply = getString(REPLY_COMMAND_SET, startSound.c_str());

			bot.message_create(dpp::message(idChannel, reply));

			printTimeOS();
			std::wcout << LOG_COMMAND_SET1 << startSound << LOG_COMMAND_SET2;
		}
		else
		{
			std::string reply = getString(REPLY_ERROR_COMMAND_SET, startSound.c_str());

			bot.message_create(dpp::message(idChannel, reply));

			printTimeOS();
			std::wcout << LOG_ERROR_COMMAND_SET1 << startSound << LOG_ERROR_COMMAND_SET2;
		}
	}
	else if (content._Starts_with(COMMAND_CHAT))
	{
		// Hỗ trợ chat nên không làm gì hết
	}
	else if (content == COMMAND_RESET)
	{
		gameManagement.resetGame();

		std::wstring currentSound = gameManagement.getCurrentSound();
		int turn = gameManagement.history.getCount() + 1;

		std::string reply = getString(REPLY_COMMAND_INFO, currentSound.c_str(), turn, "");

		bot.message_create(dpp::message(idChannel, reply));

		printTimeOS();
		std::wcout << LOG_COMMAND_RESET1 << currentSound << LOG_COMMAND_RESET2;
	}
	else if (content == COMMAND_HELP)
	{
		std::string reply = getString(REPLY_COMMAND_HELP);

		bot.message_create(dpp::message(idChannel, reply));

		printTimeOS();
		std::wcout << LOG_COMMAND_HELP;
	}
	else if (content == COMMAND_INFO)
	{
		int turn = gameManagement.history.getCount() + 1;
		std::string reply = getString(REPLY_COMMAND_INFO, currentSound.c_str(), turn);

		bot.message_create(dpp::message(idChannel, reply));
		printTimeOS();
		std::wcout << LOG_COMMAND_INFO;
	}
	else if (content == COMMAND_NO_CHECK_PLAYER)
	{
		gameManagement.isCheckPlayer = !gameManagement.isCheckPlayer;
		const wchar_t* status = (gameManagement.isCheckPlayer ? L"Bật" : L"Tắt");
		std::string reply = getString(REPLY_COMMAND_NO_CHECK_PLAYER, status);

		bot.message_create(dpp::message(idChannel, reply));
		printTimeOS();
		std::wcout << status << LOG_COMMAND_NO_CHECK_PLAYER;
	}
	else { // content không phải lệnh chương trình, content là đáp án

		ErrorAddWord errorAddWord = gameManagement.addWord(content, author->id);

		switch (errorAddWord)
		{
		case ErrorAddWord::None:
		{
			bot.message_add_reaction(idContent, idChannel, u8"💯");

			printTimeOS();
			std::wcout << LOG_ACCEPT_WORD1 << content << LOG_ACCEPT_WORD2;
			break;
		}
		case ErrorAddWord::InvalidPlayer:
		{
			std::wstring username = (std::wstring)CA2WEX(author->username.c_str(), CP_UTF8);
			std::string reply = getString(REPLY_ERROR_PLAYER, username.c_str());

			bot.message_create(dpp::message(idChannel, reply));
			bot.message_delete(idContent, idChannel);

			printTimeOS();
			std::wcout << LOG_ERROR_PLAYER1 << username << LOG_ERROR_PLAYER2;
			break;
		}
		case ErrorAddWord::InvalidCountWord:
		{
			std::string reply = getString(REPLY_ERROR_COUNT_SOUNDS, content.c_str());

			bot.message_create(dpp::message(idChannel, reply));
			bot.message_delete(idContent, idChannel);

			printTimeOS();
			std::wcout << LOG_ERROR_COUNT_SOUNDS1 << content << LOG_ERROR_COUNT_SOUNDS2;
			break;
		}
		case ErrorAddWord::CanNotRead:
		{
			std::string reply = getString(REPLY_ERROR_SOUND_CAN_NOT_READ, content.c_str());

			bot.message_delete(idContent, idChannel);
			bot.message_create(dpp::message(idChannel, reply));

			printTimeOS();
			std::wcout << LOG_ERROR_SOUND_CAN_NOT_READ1 << content << LOG_ERROR_SOUND_CAN_NOT_READ2;
			break;
		}
		case ErrorAddWord::InvalidStart:
		{
			std::string reply = getString(REPLY_ERROR_INVALID_STARTSOUND, content.c_str(), currentSound.c_str());

			bot.message_delete(idContent, idChannel);
			bot.message_create(dpp::message(idChannel, reply));

			printTimeOS();
			std::wcout << LOG_ERROR_INVALID_STARTSOUND1 << content << LOG_ERROR_INVALID_STARTSOUND2;
			break;
		}
		case ErrorAddWord::Existed:
		{
			std::string reply = getString(REPLY_ERROR_WORD_EXISTED, content.c_str());

			bot.message_create(dpp::message(idChannel, reply));
			bot.message_delete(idContent, idChannel);

			printTimeOS();
			std::wcout << LOG_ERROR_WORD_EXISTED1 << content << LOG_ERROR_WORD_EXISTED2;
			break;
		}
		case ErrorAddWord::NoMeaning:
		{
			std::string reply = getString(REPLY_ERROR_NO_MEANING, content.c_str());

			bot.message_create(dpp::message(idChannel, reply));
			bot.message_delete(idContent, idChannel);

			printTimeOS();
			std::wcout << LOG_ERROR_WORD_NOMEANING1 << content << LOG_ERROR_WORD_NOMEANING2;
			break;
		}
		case ErrorAddWord::Victory:
		{
			bot.message_add_reaction(idContent, idChannel, u8"💯");

			std::wstring username = (std::wstring)CA2WEX(author->username.c_str(), CP_UTF8);

			std::string reply = getString(REPLY_ERROR_VICTORY, content.c_str(), username.c_str());
			bot.message_create(dpp::message(idChannel, reply));

			gameManagement.resetGame();

			std::wstring startWord = gameManagement.getCurrentSound();
			reply = getString(REPLY_COMMAND_RESET, startWord.c_str());

			bot.message_create(dpp::message(idChannel, reply));

			printTimeOS();
			std::wcout << LOG_VICTORY;
			break;
		}
		default:
			break;
		}
	}
}

/// <summary>
/// Lấy std::string UTF8 sử dụng format
/// </summary>
std::string getString(const wchar_t* _Format, ...)
{
	va_list _ArgList;
	wchar_t buffer[1024];

	__crt_va_start(_ArgList, _Format);
	_vswprintf_c_l(buffer, 1024, _Format, NULL, _ArgList);
	__crt_va_end(_ArgList);

	std::string str = (std::string)CW2AEX(buffer, CP_UTF8);

	return str;
}

/// <summary>
/// Các cài đặt ban đầu cho chương trình
/// </summary>
void config()
{
	// Nhập xuất Tiếng Việt
	std::ignore = _setmode(_fileno(stdout), _O_WTEXT);
	std::ignore = _setmode(_fileno(stdin), _O_WTEXT);

	// Sử dụng để đọc file, xử lý chuỗi tiếng việt
	std::locale::global(std::locale("en_US.UTF8"));

	// ==> {{ Bot Discord }}
	/* TOKEN = "OTA1ODM1ODQ5NzA5NjYyMjA5.YYP3YA.YRcUBf-yBWr_yEgOhZUKKMvegNk"
	 * IdLocal: 905849241577074728
	 * IdGlobal: 906493073872269313 */

	token = "OTA1ODM1ODQ5NzA5NjYyMjA5.YYP3YA.YRcUBf-yBWr_yEgOhZUKKMvegNk";
	idChannel = 905849241577074728;

	//std::wstring tmp;
	//std::wcout << L"Input token bot: ";
	//std::getline(std::wcin, tmp);
	//token = (std::string)CW2AEX(tmp.c_str(), CP_UTF8);

	//std::wcout << L"Input ID Channel: ";
	//std::wcin >> idChannel;
	//std::wcin.ignore(); // ignore "\n"

}

/// <summary>
/// In thời gian hiện tại trên console
/// </summary>
void printTimeOS()
{
	wchar_t tmpbuf[128];
	_wstrtime_s(tmpbuf, 128);
	std::wcout << tmpbuf << "\t:\t";
}