#pragma once
#include <cstdint>

namespace utils::logger
{
	enum class Level
	{
		Info,
		Warning,
		Error
	};

	void init(const char* log_file_path);
	void write(Level level, const char* format, ...);
	void info(const char* format, ...);
	void warning(const char* format, ...);
	void error(const char* format, ...);
	bool is_initialized();
	void close();
}