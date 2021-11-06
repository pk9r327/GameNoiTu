#pragma once

constexpr auto WELCOME = L"Pk9rNT đã sống lại rồi đây. Trò chơi sẽ bắt đầu bằng từ `%ls`.Nếu không thích hãy sử dụng lệnh `!set <StartWord>` ta sẽ giúp ngươi thay đổi";
constexpr auto LOG_WELCOME1 = L"Đã đăng nhập vào ";
constexpr auto LOG_WELCOME2 = L"!\n";
constexpr auto COMMAND_SET = L"!set ";
constexpr auto LENGTH_COMMAND_SET = 5;
constexpr auto REPLY_COMMAND_SET = L"OK. Trò chơi sẽ bắt đầu bằng từ `%ls`";
constexpr auto LOG_COMMAND_SET1 = L"Thay đổi từ bắt đầu trò chơi thành `";
constexpr auto LOG_COMMAND_SET2 = L"\n";
constexpr auto REPLY_ERROR_COUNT_WORD = L"`%ls` không được chấp nhận, chỉ được sử dụng từ có 2 âm tiết";
constexpr auto LOG_ERROR_COUNT_WORD1 = L"Huỷ đáp án `";
constexpr auto LOG_ERROR_COUNT_WORD2 = L"` vì từ số âm tiết không hợp lệ\n";
constexpr auto LOG_ACCEPT_WORD1 = L"Chấp nhận đáp án `";
constexpr auto LOG_ACCEPT_WORD2 = L"\n";
constexpr auto REPLY_ERROR_INVALID_STARTWORD = L"`%ls` không được chấp nhận, hãy bắt đầu từ bằng `%ls`";
constexpr auto LOG_ERROR_INVALID_STARTWORD1 = L"Huỷ đáp án `";
constexpr auto LOG_ERROR_INVALID_STARTWORD2 = L"` vì từ bắt đầu không hợp lệ\n";
constexpr auto REPLY_ERROR_WORD_EXISTED = L"`%ls` đã được sử dụng, vui lòng thử từ khác";
constexpr auto LOG_ERROR_WORD_EXISTED1 = L"Huỷ đáp án`";
constexpr auto LOG_ERROR_WORD_EXISTED2 = L"` vì từ đã được sử dụng\n";