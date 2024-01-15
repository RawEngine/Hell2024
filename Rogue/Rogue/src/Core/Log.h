
#pragma once

class Log
{
public:
	// IMPORTANT: Don't forget to update "Log::ChannelToString".
	enum class Channel
	{
		Main,
		FileSystem,
		AssetSystem,
		Renderer,
		Physics,
		Audio
	};

	enum class Level
	{
		Debug,
		Info,
		Warning,
		Error
	};

	Log(const std::filesystem::path& fileName);
	~Log();

	static std::string ChannelToString(Channel channel);
	static char LevelToChar(Level level);

	void WriteVA(Channel channel, Level level, int line, const char* pFuncName, const char* pFormat, ...);
	void Write(Channel channel, Level level, int line, const char* pFuncName, const std::string& message);


private:
	std::ofstream _file;
};

extern Log* gpLog;

#define LOG_DEBUG(channel, ...)		gpLog->WriteVA(channel, Log::Level::Debug, __LINE__, __FUNCTION__, __VA_ARGS__)
#define LOG_MESSAGE(channel, ...)	gpLog->WriteVA(channel, Log::Level::Info, __LINE__, __FUNCTION__, __VA_ARGS__)
#define LOG_WARNING(channel, ...)	gpLog->WriteVA(channel, Log::Level::Warning, __LINE__, __FUNCTION__, __VA_ARGS__)
#define LOG_ERROR(channel, ...)		gpLog->WriteVA(channel, Log::Level::Error, __LINE__, __FUNCTION__, __VA_ARGS__)
