#include <cstdio>
#include <cstdarg>
#include <ctime>
#include "include/utils/logger.h"
#include "include/utils/win32_lean.h"

namespace utils::logger
{
	static HANDLE log_file = INVALID_HANDLE_VALUE;
	static CRITICAL_SECTION cs;
	static bool initialized = false;

	void init(const char* log_file_path)
	{
		if (initialized)
			return;

		InitializeCriticalSection(&cs);

		char full_path[MAX_PATH];
		char module_path[MAX_PATH];

		HMODULE module = nullptr;
		GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
			(LPCSTR)&init, &module);

		if (module)
		{
			GetModuleFileNameA(module, module_path, sizeof(module_path));

			char* last_slash = strrchr(module_path, '\\');
			if (last_slash)
			{
				*(last_slash + 1) = '\0';
				snprintf(full_path, sizeof(full_path), "%s%s", module_path, log_file_path);
			}
			else
			{
				strncpy_s(full_path, sizeof(full_path), log_file_path, _TRUNCATE);
			}
		}
		else
		{
			strncpy_s(full_path, sizeof(full_path), log_file_path, _TRUNCATE);
		}

		log_file = CreateFileA(
			full_path,
			GENERIC_WRITE,
			FILE_SHARE_READ,
			nullptr,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			nullptr
		);

		if (log_file != INVALID_HANDLE_VALUE)
		{
			SetFilePointer(log_file, 0, nullptr, FILE_END);
			initialized = true;

			char timestamp[64];
			time_t now = time(nullptr);
			tm local_time;
			localtime_s(&local_time, &now);
			strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &local_time);

			char header[512];
			int len = snprintf(header, sizeof(header), "\r\n========== Logger initialized at %s ==========\r\nLog file: %s\r\n", timestamp, full_path);

			DWORD written;
			WriteFile(log_file, header, len, &written, nullptr);
			FlushFileBuffers(log_file);
		}
	}

	void write(Level level, const char* format, ...)
	{
		if (!initialized || log_file == INVALID_HANDLE_VALUE)
			return;

		EnterCriticalSection(&cs);

		char timestamp[64];
		time_t now = time(nullptr);
		tm local_time;
		localtime_s(&local_time, &now);
		strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &local_time);

		const char* level_str;
		switch (level)
		{
			case Level::Info:    level_str = "INFO"; break;
			case Level::Warning: level_str = "WARN"; break;
			case Level::Error:   level_str = "ERROR"; break;
			default:             level_str = "UNKNOWN"; break;
		}

		char buffer[2048];
		int offset = snprintf(buffer, sizeof(buffer), "[%s] [%s] ", timestamp, level_str);

		if (offset > 0 && offset < sizeof(buffer) - 3)
		{
			va_list args;
			va_start(args, format);
			int written = vsnprintf(buffer + offset, sizeof(buffer) - offset - 2, format, args);
			va_end(args);

			if (written > 0)
				offset += written;

			if (offset < sizeof(buffer) - 2)
			{
				buffer[offset++] = '\r';
				buffer[offset++] = '\n';
				buffer[offset] = '\0';
			}
		}

		DWORD written;
		WriteFile(log_file, buffer, offset, &written, nullptr);
		FlushFileBuffers(log_file);

		LeaveCriticalSection(&cs);
	}

	void info(const char* format, ...)
	{
		if (!initialized)
			return;

		char buffer[2048];
		va_list args;
		va_start(args, format);
		vsnprintf(buffer, sizeof(buffer), format, args);
		va_end(args);

		write(Level::Info, "%s", buffer);
	}

	void warning(const char* format, ...)
	{
		if (!initialized)
			return;

		char buffer[2048];
		va_list args;
		va_start(args, format);
		vsnprintf(buffer, sizeof(buffer), format, args);
		va_end(args);

		write(Level::Warning, "%s", buffer);
	}

	void error(const char* format, ...)
	{
		if (!initialized)
			return;

		char buffer[2048];
		va_list args;
		va_start(args, format);
		vsnprintf(buffer, sizeof(buffer), format, args);
		va_end(args);

		write(Level::Error, "%s", buffer);
	}

	bool is_initialized()
	{
		return initialized;
	}

	void close()
	{
		if (!initialized)
			return;

		if (log_file != INVALID_HANDLE_VALUE)
		{
			CloseHandle(log_file);
			log_file = INVALID_HANDLE_VALUE;
		}

		DeleteCriticalSection(&cs);
		initialized = false;
	}
}
