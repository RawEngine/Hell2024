
// TODO: Move to PCH.h (Precompiled header)
#include "Log.h"
#include "Exception.h"

#include <stdarg.h>
#include <sstream>
#include <chrono>
#include <filesystem>

namespace
{
	std::string StringFromLocaltime(bool needsDate, bool needsTime, bool needsMS)
	{
		auto now = std::chrono::system_clock::now();
		auto posixTime = std::chrono::system_clock::to_time_t(now);

		std::tm tp;
		localtime_s(&tp, &posixTime);

		std::string format;

		if (needsDate && needsTime)
			format = "%Y-%m-%d %H:%M:%S";
		else if (needsDate)
			format = "%Y-%m-%d";
		else
			format = "%H:%M:%S";

		std::ostringstream ss;

		char foo[24];
		strftime(foo, sizeof(foo), format.c_str(), &tp);

		ss << foo;

		if (needsMS)
		{
			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

			ss.fill('0');
			ss << '.' << std::setw(3) << ms.count();
		}

		return ss.str();
	}
}

Log* gpLog = nullptr;

Log::Log(const std::filesystem::path& fileName)
	: _file(fileName, std::ios_base::out | std::ios_base::trunc)
{
	if (!_file.is_open())
		THROW_EXCEPTION_VA("Failed to open the log file: %s", fileName.string().c_str());

	gpLog = this;

	Write(Channel::Main, Level::Info, __LINE__, __FUNCTION__, "Start.");
}

Log::~Log()
{
	Write(Channel::Main, Level::Info, __LINE__, __FUNCTION__, "End.");
}

void Log::WriteVA(Channel channel, Level level, int line, const char* pFuncName, const char* pFormat, ...)
{
	constexpr int LogLineMaxLength = 2048;

	static char buffer[LogLineMaxLength];

	va_list args;
	va_start(args, pFormat);

	const size_t length = _vsnprintf_s(buffer, sizeof(buffer) - 1, pFormat, args);

	va_end(args);

	// Ensure null-termination of the string
	if (length > 0 && length < sizeof(buffer))
		buffer[length] = '\0';
	else
		buffer[sizeof(buffer) - 1] = '\0'; // Make sure the string is null-terminated in case of truncation or error

	auto test = std::string(buffer, static_cast<size_t>(length));

	Write(channel, level, line, pFuncName, test);
}

void Log::Write(Channel channel, Level level, int line, const char* pFuncName, const std::string& message)
{
	std::ostringstream ss;

	ss << '[' << StringFromLocaltime(false, true, true) << "] | ";
	ss << '[' << Log::ChannelToString(channel) << "]\t|";

	ss << Log::LevelToChar(level) << " | " << message;

	if (level == Level::Error)
		ss << " (Func: " << pFuncName << ", Line: " << line << ")";

#if _DEBUG
	std::cout << ss.str() << std::endl;
#endif
	_file << ss.str() << "\n";
	_file.flush();
}

std::string Log::ChannelToString(Channel channel)
{
	static const char* channelStrings[] = {
		"Main",
		"FileSystem",
		"AssetSystem",
		"Renderer",
		"Physics",
		"Audio"
	};

	int channelIndex = static_cast<int>(channel);
	if (channelIndex >= 0 && channelIndex < static_cast<int>(sizeof(channelStrings) / sizeof(channelStrings[0])))
		return channelStrings[channelIndex];

	return "???";
}

char Log::LevelToChar(Level level)
{
	static const char levelChars[] = {
		'D', // Level::Debug
		'I', // Level::Info
		'W', // Level::Warning
		'E'  // Level::Error
	};

	int levelIndex = static_cast<int>(level);
	if (levelIndex >= 0 && levelIndex < static_cast<int>(sizeof(levelChars) / sizeof(levelChars[0])))
		return levelChars[levelIndex];

	return '?';
}
