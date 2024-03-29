﻿#pragma once
#include "History.h" // History
#include "Dictionary.h" // Dictionary
#include "RandomSound.h" // RandomWord

enum class ErrorAddWord
{
	/// <summary>
	/// Chấp nhận kết quả
	/// </summary>
	None,

	/// <summary>
	/// Người gửi đã chơi lượt trước đó, huỷ kết quả
	/// </summary>
	InvalidPlayer,

	/// <summary>
	/// Số lượng âm tiết của từ không hợp lệ, huỷ kết quả
	/// </summary>
	InvalidCountWord,

	/// <summary>
	/// Từ không phải tiếng việt có thể đọc, huỷ kết quả
	/// </summary>
	CanNotRead,

	/// <summary>
	/// Từ có âm bắt đầu không hợp lệ, huỷ kết quả
	/// </summary>
	InvalidStart,

	/// <summary>
	/// Từ đã được sử dụng trước đó trong màn chơi, huỷ kết quả
	/// </summary>
	Existed,

	/// <summary>
	/// Từ không có nghĩa, huỷ kết quả
	/// </summary>
	NoMeaning,

	/// <summary>
	/// Kết thúc trò chơi và tìm được người chiến thắng
	/// </summary>
	Victory
};

/// <summary>
/// Đối tượng quản lý một trò chơi
/// </summary>
class GameManagement
{

public:
	/// <summary>
	/// Điều kiện kiểm tra chơi người chơi
	/// </summary>
	bool isCheckPlayer;

	GameManagement()
	{
		isCheckPlayer = true;
		resetGame();
	}

	ErrorAddWord addWord(const std::wstring& word, const uint64_t& idPlayer)
	{
		// Kiểm tra tính hợp lệ của người trả lời
		if (isCheckPlayer && idPlayer == lastIdPlayer)
			return ErrorAddWord::InvalidPlayer;

		// Kiểm tra số âm tiết của từ
		if (std::count(word.begin(), word.end(), L' ') != 1)
			return ErrorAddWord::InvalidCountWord;

		std::wstring vs[2];
		EncoderTiengViet::splitString(word, vs);
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();

		// Kiểm tra tính hợp lệ của âm bắt đầu
		if (!encoderTiengViet->isEquals(vs[0], currentSound))
		{
			return ErrorAddWord::InvalidStart;
		}

		// Kiểm tra tính đọc được của từ
		uint16_t encoded = encoderTiengViet->encodingSoundToUInt16(vs[1]);
		if (encoded == UINT16_MAX)
		{
			return ErrorAddWord::CanNotRead;
		}

		//Kiểm tra tính có nghĩa của từ
		Dictionary* dictionary = dictionary->getInstance();
		if (!dictionary->checkMeaning(word))
		{
			return ErrorAddWord::NoMeaning;
		}

		bool isAddSuccessed = history.add(word);
		if (isAddSuccessed)
		{
			currentSound = vs[1];
			lastIdPlayer = idPlayer;

			uint16_t encode1 = encoderTiengViet->encodingSoundToUInt16(currentSound);

			MyArray<uint16_t>* lastSounds = dictionary->getLastSounds(encode1);

			if (lastSounds != nullptr)
			{
				for (int i = 0; i < lastSounds->getSize(); i++)
				{
					uint16_t encode2 = (*lastSounds)[i];

					uint32_t encode = (encode1 << 16) + encode2;

					if (!history.isExisted(encode))
						return ErrorAddWord::None;
				}
			}

			return ErrorAddWord::Victory;
		}
		else
		{
			return ErrorAddWord::Existed;
		}
	}

	/// <summary>
	/// Khởi động lại trò chơi
	/// </summary>
	void resetGame()
	{
		RandomSound* randomSound = randomSound->getInstance();
		currentSound = randomSound->getRandomStartSound();
		history.removeAll();
		lastIdPlayer = 0;
	}

	/// <summary>
	/// Khởi động lại trò chơi với một âm bắt đầu tuỳ chọn
	/// </summary>
	/// <param name="startSound">Âm bắt đầu trò chơi</param>
	/// <returns>
	///		<para>true: Khởi động lại thành công</para>
	///		<para>false: Khởi động lại không thành công (âm bắt đầu không hợp lệ)</para>
	/// </returns>
	bool resetGame(const std::wstring& startSound)
	{
		EncoderTiengViet* encoderTiengViet = encoderTiengViet->getInstance();
		uint16_t encoded = encoderTiengViet->encodingSoundToUInt16(startSound);
		if (encoded == UINT16_MAX)
		{
			return false;
		}

		currentSound = startSound;
		history.removeAll();
		return true;
	}

	/// <summary>
	/// Lấy âm băt đầu hiện tại của màn chơi
	/// </summary>
	/// <returns></returns>
	std::wstring getCurrentSound()
	{
		return currentSound;
	}

	/// <summary>
	/// Cây chứa mã hoá các từ đã sử dụng trong màn chơi
	/// </summary>
	History history;

private:

	/// <summary>
	/// Âm bắt đầu hiện tại của màn chơi
	/// </summary>
	std::wstring currentSound;

	/// <summary>
	/// Người trả lời cuối cùng trong màn chơi
	/// </summary>
	uint64_t lastIdPlayer;
};