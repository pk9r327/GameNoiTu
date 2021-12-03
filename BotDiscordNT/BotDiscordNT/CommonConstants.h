#pragma once

#pragma region Log console
constexpr auto LOG_WELCOME1 = L"Đã đăng nhập vào ";
constexpr auto LOG_WELCOME2 = L"!\n";

constexpr auto LOG_COMMAND_SET1 = L"Thay đổi âm bắt đầu trò chơi thành `";
constexpr auto LOG_COMMAND_SET2 = L"`\n";

constexpr auto LOG_COMMAND_RESET1 = L"Bắt đầu lại trò chơi với âm `";
constexpr auto LOG_COMMAND_RESET2 = L"`\n";

constexpr auto LOG_COMMAND_HELP = L"Hiện thị hướng dẫn\n";

constexpr auto LOG_COMMAND_INFO = L"Hiện thị thông tin màn chơi\n";

constexpr auto LOG_ERROR_COMMAND_SET1 = L"Huỷ lệnh `!set ";
constexpr auto LOG_ERROR_COMMAND_SET2 = L"` vì âm cài đặt không hợp lệ\n";

constexpr auto LOG_ERROR_PLAYER1 = L"Huỷ đáp án của người chơi `";
constexpr auto LOG_ERROR_PLAYER2 = L"` vì người chơi đã hết lượt\n";

constexpr auto LOG_ERROR_COUNT_SOUNDS1 = L"Huỷ đáp án `";
constexpr auto LOG_ERROR_COUNT_SOUNDS2 = L"` vì từ số lượng âm tiết không hợp lệ\n";

constexpr auto LOG_ERROR_SOUND_CAN_NOT_READ1 = L"Huỷ đáp án `";
constexpr auto LOG_ERROR_SOUND_CAN_NOT_READ2 = L"` âm sử dụng không hợp lệ\n";

constexpr auto LOG_ERROR_INVALID_STARTSOUND1 = L"Huỷ đáp án `";
constexpr auto LOG_ERROR_INVALID_STARTSOUND2 = L"` vì âm bắt đầu không hợp lệ\n";

constexpr auto LOG_ERROR_WORD_EXISTED1 = L"Huỷ đáp án`";
constexpr auto LOG_ERROR_WORD_EXISTED2 = L"` vì từ đã được sử dụng\n";

constexpr auto LOG_ACCEPT_WORD1 = L"Chấp nhận đáp án `";
constexpr auto LOG_ACCEPT_WORD2 = L"`\n";

constexpr auto LOG_VICTORY = L"Kết thúc trò chơi\n";
#pragma endregion


#pragma region Bot reply
constexpr auto REPLY_WELCOME = L"Pk9rNT đã online\nKhởi động trò chơi hoàn tất \nĐể xem danh sách các lệnh, vui lòng dùng lệnh `!help`";

constexpr auto REPLY_COMMAND_SET = L"Thiết lập hoàn tất. Trò chơi sẽ bắt đầu bằng từ `%ls`";

constexpr auto REPLY_ERROR_COMMAND_SET = L"Không thể bắt đầu trò chơi bằng từ `%ls`, chỉ chấp nhận các từ Tiếng Việt có thể đọc";

constexpr auto REPLY_COMMAND_RESET = L"Trò chơi sẽ bắt đầu bằng từ `%ls`";

constexpr auto REPLY_ERROR_PLAYER = L"`%ls` ơi, hãy để người khác trả lời nhé, bạn đã sử dụng lượt trước đó rồi";

constexpr auto REPLY_ERROR_COUNT_SOUNDS = L"`%ls` không được chấp nhận, chỉ được sử dụng từ có 2 âm tiết";

constexpr auto REPLY_ERROR_SOUND_CAN_NOT_READ = L"`%ls` không được chấp nhận, chỉ chấp nhận các từ Tiếng Việt có thể đọc";

constexpr auto REPLY_ERROR_INVALID_STARTSOUND = L"`%ls` không được chấp nhận, hãy bắt đầu từ bằng `%ls`";

constexpr auto REPLY_ERROR_WORD_EXISTED = L"`%ls` đã được sử dụng, vui lòng thử từ khác";

constexpr auto REPLY_ERROR_NO_MEANING = L"`%ls` không có nghĩa, vui lòng thử từ khác";

constexpr auto REPLY_ERROR_VICTORY = L"Trò chơi đã kết thúc với từ `%ls`, người chiến thắng là `%s`";

constexpr auto REPLY_COMMAND_HELP =
L"< Các lệnh của Pk9rNT >\n\
`!set <StartSound>`: Thiết lập âm <StartSound> thành âm để bắt đầu trò chơi\n\
`!info`: Xem thông tin hiện tại của trò chơi\n\
`!reset`: Bắt đầu lại trò chơi";

constexpr auto REPLY_COMMAND_INFO =
L"Âm bắt đầu hiện tại: `%ls`\n\
Lượt chơi thứ: %d";
#pragma endregion


#pragma region Command
constexpr auto COMMAND_SET = L"!set ";
constexpr auto LENGTH_COMMAND_SET = 5;
constexpr auto COMMAND_CHAT = L"> ";
constexpr auto COMMAND_RESET = L"!reset";
constexpr auto COMMAND_INFO = L"!info";
constexpr auto COMMAND_HELP = L"!help";
#pragma endregion

