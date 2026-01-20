#pragma once
#include <cstdint>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

namespace database
{
	struct Connection
	{
		SQLHENV env;
		SQLHDBC dbc;
		SQLHSTMT stmt;
		bool connected;

		Connection();
		~Connection();

		bool connect(const char* database);
		bool execute(const char* query);
		bool fetch();
		bool get_string(uint16_t column, char* buffer, size_t buffer_size);
		bool get_int(uint16_t column, int32_t* value);
		bool get_bigint(uint16_t column, int64_t* value);
		bool get_byte(uint16_t column, uint8_t* value);
		bool get_short(uint16_t column, uint16_t* value);
		bool get_float(uint16_t column, float* value);
		void close();
	};
}
