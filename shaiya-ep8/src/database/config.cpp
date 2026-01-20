#include <cstdio>
#include <cstring>
#include "include/database/config.h"
#include "include/utils/ini_reader.h"
#include "include/utils/logger.h"
#include "include/utils/win32_lean.h"

namespace database::config
{
	static char server[256];
	static char username[128];
	static char password[128];
	static bool trusted_connection;

	void init()
	{
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
				snprintf(full_path, sizeof(full_path), "%sdatabase.ini", module_path);
			}
			else
			{
				strncpy_s(full_path, sizeof(full_path), "database.ini", _TRUNCATE);
			}
		}
		else
		{
			strncpy_s(full_path, sizeof(full_path), "database.ini", _TRUNCATE);
		}

		utils::logger::info("Loading database configuration from %s", full_path);

		utils::ini::read_string(full_path, "Database", "Server", server, sizeof(server), "localhost\\SQLEXPRESS");
		utils::ini::read_string(full_path, "Database", "Username", username, sizeof(username), "");
		utils::ini::read_string(full_path, "Database", "Password", password, sizeof(password), "");
		trusted_connection = utils::ini::read_bool(full_path, "Database", "TrustedConnection", true);

		utils::logger::info("Database config loaded: Server=%s, TrustedConnection=%s",
			server, trusted_connection ? "yes" : "no");
	}

	const char* get_server()
	{
		return server;
	}

	const char* get_username()
	{
		return username;
	}

	const char* get_password()
	{
		return password;
	}

	bool use_trusted_connection()
	{
		return trusted_connection;
	}
}
