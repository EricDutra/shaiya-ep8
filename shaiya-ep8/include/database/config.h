#pragma once

namespace database::config
{
	void init();
	const char* get_server();
	const char* get_username();
	const char* get_password();
	bool use_trusted_connection();
}