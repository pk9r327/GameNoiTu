#include "Main.h"

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

	bot.on_ready([&bot](const dpp::ready_t& event) {
		std::wstring currentWord = gameManagement.getCurrentWord();

		wchar_t buffer[256];
		swprintf(buffer, 256, WELCOME, currentWord.c_str());
		std::string welcome = (std::string)CW2AEX(buffer, CP_UTF8);
		bot.message_create(dpp::message(idChannel, welcome));
		printTimeOS();
		std::wcout << LOG_WELCOME1 << bot.me.username.c_str() << LOG_WELCOME2;
		});

	bot.on_message_create([&bot](const dpp::message_create_t& event) {

		if (event.msg->channel_id != idChannel)
			return;

		if (event.msg->author->id == bot.me.id)
			return;

		std::wstring content = (std::wstring)CA2WEX(event.msg->content.c_str(), CP_UTF8);
		std::wstring currentWord = gameManagement.getCurrentWord();

		if (content == L"!ping") {
			bot.message_create(dpp::message(idChannel, "Pong!"));
		}
		else if (content._Starts_with(COMMAND_SET)) {
			std::wstring startWord = content.substr(LENGTH_COMMAND_SET);
			gameManagement.resetGame(startWord);
			wchar_t buffer[256];
			swprintf(buffer, 256, REPLY_COMMAND_SET, startWord.c_str());
			std::string reply = (std::string)CW2AEX(buffer, CP_UTF8);
			bot.message_create(dpp::message(idChannel, reply));
			printTimeOS();
			std::wcout << LOG_COMMAND_SET1 << startWord << LOG_COMMAND_SET2;
		}
		else if (std::count(content.begin(), content.end(), L' ') != 1)
		{
			wchar_t buffer[256];
			swprintf(buffer, 256, REPLY_ERROR_COUNT_WORD, content.c_str());
			std::string reply = (std::string)CW2AEX(buffer, CP_UTF8);
			bot.message_create(dpp::message(idChannel, reply));
			bot.message_delete(event.msg->id, idChannel);
			printTimeOS();
			std::wcout << LOG_ERROR_COUNT_WORD1 << content << LOG_ERROR_COUNT_WORD2;
		}
		else {
			ErrorAddWord errorAddWord = gameManagement.addWord(content);

			switch (errorAddWord)
			{
			case ErrorAddWord::None:
			{
				bot.message_add_reaction(event.msg->id, idChannel, u8"💯");
				printTimeOS();
				std::wcout << LOG_ACCEPT_WORD1 << content << LOG_ACCEPT_WORD2;
				break;
			}
			case ErrorAddWord::InvalidStart:
			{
				wchar_t buffer[256];
				swprintf(buffer, 256, REPLY_ERROR_INVALID_STARTWORD, content.c_str(), currentWord.c_str());
				std::string reply = (std::string)CW2AEX(buffer, CP_UTF8);
				bot.message_delete(event.msg->id, idChannel);
				bot.message_create(dpp::message(idChannel, reply));
				printTimeOS();
				std::wcout << LOG_ERROR_INVALID_STARTWORD1 << content << LOG_ERROR_INVALID_STARTWORD2;
				break;
			}
			case ErrorAddWord::Existed:
			{
				wchar_t buffer[256];
				swprintf(buffer, 256, REPLY_ERROR_WORD_EXISTED, content.c_str());
				std::string reply = (std::string)CW2AEX(buffer, CP_UTF8);
				bot.message_create(dpp::message(idChannel, reply));
				bot.message_delete(event.msg->id, idChannel);
				printTimeOS();
				std::wcout << LOG_ERROR_WORD_EXISTED1 << content << LOG_ERROR_WORD_EXISTED2;
				break;
			}
			case ErrorAddWord::NoMeaning:
				break;
			default:
				break;
			}
		}
		});
	bot.start(false);
}

void config()
{
	std::ignore = _setmode(_fileno(stdout), _O_WTEXT);
	std::ignore = _setmode(_fileno(stdin), _O_WTEXT);

	// Sử dụng để đọc file, xử lý chuỗi tiếng việt
	std::locale::global(std::locale("en_US.UTF8"));

	// ==> {{ Bot Discord }}
	/* TOKEN = "OTA1ODM1ODQ5NzA5NjYyMjA5.YYP3YA.YRcUBf-yBWr_yEgOhZUKKMvegNk"
	 * IdChannel: 905849241577074728 */

	 //std::wstring tmp;
	 //std::wcout << L"Input token bot: ";
	 //std::getline(std::wcin, tmp);
	 //token = (std::string)CW2AEX(tmp.c_str(), CP_UTF8);
	 //std::wcout << L"Input ID Channel: ";
	 //std::wcin >> idChannel;
	 //std::wcin.ignore(); // ignore "\n"
	token = "OTA1ODM1ODQ5NzA5NjYyMjA5.YYP3YA.YRcUBf-yBWr_yEgOhZUKKMvegNk";
	idChannel = 905849241577074728;
}

void printTimeOS()
{
	wchar_t tmpbuf[128];
	_wstrtime_s(tmpbuf, 128);
	std::wcout << tmpbuf << "\t:\t";
}