#pragma once
#include "EncoderTiengViet.h" // splitString
#include <random>


/// <summary>
/// Sử dụng dữ liệu từ tệp từ điển, chọn âm ngẫu nhiên trong từ điển
/// </summary>
class RandomSound
{
public:

	/// <summary>
	/// Singleton Instance 
	/// (đối tượng RandomSound duy nhất trong suốt quá trình chạy của chương trình)
	/// </summary>
	/// <returns></returns>
	static RandomSound* getInstance()
	{
		if (!instance)
			instance = new RandomSound;
		return instance;
	}

	/// <summary>
	/// Lấy một âm ngẫu nhiên trong từ điển
	/// </summary>
	/// <returns></returns>
	std::wstring getRandomStartSound()
	{
		int index = distr(eng);
		return startSounds[index];
	}

private:

	/// <summary>
	/// Số lượng phần từ của mảng startWords
	/// </summary>
	int sizeStartSounds;

	/// <summary>
	/// Mảng chưa các từ bắt đầu trong từ điển
	/// </summary>
	std::wstring* startSounds;


	std::default_random_engine eng;
	std::uniform_int_distribution<int> distr;

	static RandomSound* instance;

	RandomSound()
	{
		std::wifstream rf("start_word.txt");
		rf.imbue(std::locale()); // sử dụng để đọc file Tiếng Việt

		rf >> sizeStartSounds;
		rf.ignore(); // ignore \n

		std::wstring line;

		startSounds = new std::wstring[sizeStartSounds];
		std::getline(rf, line);
		EncoderTiengViet::splitString(line, startSounds, L",");

		rf.close();

		std::random_device rd;
		eng = std::default_random_engine(rd());
		distr = std::uniform_int_distribution<int>(0, sizeStartSounds - 1);
	}

};

//Initialize pointer to zero so that it can be initialized in first call to getInstance
RandomSound* RandomSound::instance = nullptr;