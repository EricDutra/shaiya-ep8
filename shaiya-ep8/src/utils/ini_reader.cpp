#include <cstring>
#include "include/utils/ini_reader.h"
#include "include/utils/win32_lean.h"

namespace utils::ini
{
	bool read_string(const char* file_path, const char* section, const char* key, char* buffer, size_t buffer_size, const char* default_value)
	{
		if (!file_path || !section || !key || !buffer)
			return false;

		DWORD result = GetPrivateProfileStringA(section, key, default_value, buffer, buffer_size, file_path);
		return result > 0;
	}

	int32_t read_int(const char* file_path, const char* section, const char* key, int32_t default_value)
	{
		if (!file_path || !section || !key)
			return default_value;

		return GetPrivateProfileIntA(section, key, default_value, file_path);
	}

	bool read_bool(const char* file_path, const char* section, const char* key, bool default_value)
	{
		char buffer[32];
		if (!read_string(file_path, section, key, buffer, sizeof(buffer), default_value ? "true" : "false"))
			return default_value;

		if (strcmp(buffer, "true") == 0 || strcmp(buffer, "1") == 0 || strcmp(buffer, "yes") == 0)
			return true;

		if (strcmp(buffer, "false") == 0 || strcmp(buffer, "0") == 0 || strcmp(buffer, "no") == 0)
			return false;

		return default_value;
	}
}