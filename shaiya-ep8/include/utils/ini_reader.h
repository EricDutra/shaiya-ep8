#pragma once
#include <cstdint>

namespace utils::ini
{
	bool read_string(const char* file_path, const char* section, const char* key, char* buffer, size_t buffer_size, const char* default_value);
	int32_t read_int(const char* file_path, const char* section, const char* key, int32_t default_value);
	bool read_bool(const char* file_path, const char* section, const char* key, bool default_value);
}