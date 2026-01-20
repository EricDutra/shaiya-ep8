#include <cstdio>
#include <cstring>
#include "include/database/connection.h"
#include "include/database/config.h"
#include "include/utils/logger.h"

namespace database
{
	static void get_sql_error(SQLHANDLE handle, SQLSMALLINT handle_type, char* buffer, size_t buffer_size)
	{
		SQLCHAR sql_state[6];
		SQLINTEGER native_error;
		SQLCHAR error_msg[512];
		SQLSMALLINT msg_len;

		if (SQLGetDiagRecA(handle_type, handle, 1, sql_state, &native_error, error_msg, sizeof(error_msg), &msg_len) == SQL_SUCCESS)
		{
			snprintf(buffer, buffer_size, "[%s] %s (Native Error: %d)", sql_state, error_msg, native_error);
		}
		else
		{
			snprintf(buffer, buffer_size, "Unable to retrieve error message");
		}
	}

	Connection::Connection() : env(nullptr), dbc(nullptr), stmt(nullptr), connected(false)
	{
	}

	Connection::~Connection()
	{
		close();
	}

	bool Connection::connect(const char* database)
	{
		if (connected)
			return true;

		utils::logger::info("Attempting to connect to database: %s on server: %s", database, config::get_server());

		if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env) != SQL_SUCCESS)
		{
			utils::logger::error("Failed to allocate ODBC environment handle");
			return false;
		}

		SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

		if (SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc) != SQL_SUCCESS)
		{
			char error[512];
			get_sql_error(env, SQL_HANDLE_ENV, error, sizeof(error));
			utils::logger::error("Failed to allocate ODBC connection handle: %s", error);
			SQLFreeHandle(SQL_HANDLE_ENV, env);
			return false;
		}

		char conn_str[512];
		if (config::use_trusted_connection())
		{
			snprintf(conn_str, sizeof(conn_str), "Driver={SQL Server};Server=%s;Database=%s;Trusted_Connection=yes;", config::get_server(), database);
		}
		else
		{
			snprintf(conn_str, sizeof(conn_str), "Driver={SQL Server};Server=%s;Database=%s;UID=%s;PWD=%s;", config::get_server(), database, config::get_username(), config::get_password());
		}

		SQLSMALLINT out_len;
		SQLRETURN ret = SQLDriverConnectA(dbc, nullptr, (SQLCHAR*)conn_str, SQL_NTS, nullptr, 0, &out_len, SQL_DRIVER_NOPROMPT);

		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			char error[512];
			get_sql_error(dbc, SQL_HANDLE_DBC, error, sizeof(error));
			utils::logger::error("Failed to connect to database %s: %s", database, error);
			SQLFreeHandle(SQL_HANDLE_DBC, dbc);
			SQLFreeHandle(SQL_HANDLE_ENV, env);
			return false;
		}

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt) != SQL_SUCCESS)
		{
			char error[512];
			get_sql_error(dbc, SQL_HANDLE_DBC, error, sizeof(error));
			utils::logger::error("Failed to allocate ODBC statement handle: %s", error);
			SQLDisconnect(dbc);
			SQLFreeHandle(SQL_HANDLE_DBC, dbc);
			SQLFreeHandle(SQL_HANDLE_ENV, env);
			return false;
		}

		connected = true;
		utils::logger::info("Successfully connected to database: %s", database);
		return true;
	}

	bool Connection::execute(const char* query)
	{
		if (!connected || !stmt)
		{
			utils::logger::error("Execute failed: not connected or invalid statement handle");
			return false;
		}

		SQLFreeStmt(stmt, SQL_CLOSE);
		SQLRETURN ret = SQLExecDirectA(stmt, (SQLCHAR*)query, SQL_NTS);

		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			char error[512];
			get_sql_error(stmt, SQL_HANDLE_STMT, error, sizeof(error));
			utils::logger::error("Query execution failed: %s", error);
			utils::logger::error("Query was: %s", query);
			return false;
		}

		return true;
	}

	bool Connection::fetch()
	{
		if (!connected || !stmt)
			return false;

		SQLRETURN ret = SQLFetch(stmt);
		return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
	}

	bool Connection::get_string(uint16_t column, char* buffer, size_t buffer_size)
	{
		if (!connected || !stmt || !buffer)
			return false;

		SQLLEN indicator;
		SQLRETURN ret = SQLGetData(stmt, column, SQL_C_CHAR, buffer, buffer_size, &indicator);

		if (indicator == SQL_NULL_DATA)
			buffer[0] = '\0';

		return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
	}

	bool Connection::get_int(uint16_t column, int32_t* value)
	{
		if (!connected || !stmt || !value)
			return false;

		SQLLEN indicator;
		SQLRETURN ret = SQLGetData(stmt, column, SQL_C_SLONG, value, sizeof(int32_t), &indicator);

		if (indicator == SQL_NULL_DATA)
			*value = 0;

		return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
	}

	bool Connection::get_bigint(uint16_t column, int64_t* value)
	{
		if (!connected || !stmt || !value)
			return false;

		SQLLEN indicator;
		SQLRETURN ret = SQLGetData(stmt, column, SQL_C_SBIGINT, value, sizeof(int64_t), &indicator);

		if (indicator == SQL_NULL_DATA)
			*value = 0;

		return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
	}

	bool Connection::get_byte(uint16_t column, uint8_t* value)
	{
		if (!connected || !stmt || !value)
			return false;

		SQLLEN indicator;
		SQLRETURN ret = SQLGetData(stmt, column, SQL_C_UTINYINT, value, sizeof(uint8_t), &indicator);

		if (indicator == SQL_NULL_DATA)
			*value = 0;

		return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
	}

	bool Connection::get_short(uint16_t column, uint16_t* value)
	{
		if (!connected || !stmt || !value)
			return false;

		SQLLEN indicator;
		SQLRETURN ret = SQLGetData(stmt, column, SQL_C_USHORT, value, sizeof(uint16_t), &indicator);

		if (indicator == SQL_NULL_DATA)
			*value = 0;

		return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
	}

	bool Connection::get_float(uint16_t column, float* value)
	{
		if (!connected || !stmt || !value)
			return false;

		SQLLEN indicator;
		SQLRETURN ret = SQLGetData(stmt, column, SQL_C_FLOAT, value, sizeof(float), &indicator);

		if (indicator == SQL_NULL_DATA)
			*value = 0.0f;

		return (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO);
	}

	void Connection::close()
	{
		if (stmt)
			SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		if (dbc)
		{
			SQLDisconnect(dbc);
			SQLFreeHandle(SQL_HANDLE_DBC, dbc);
		}
		if (env)
			SQLFreeHandle(SQL_HANDLE_ENV, env);

		env = nullptr;
		dbc = nullptr;
		stmt = nullptr;
		connected = false;
	}
}
