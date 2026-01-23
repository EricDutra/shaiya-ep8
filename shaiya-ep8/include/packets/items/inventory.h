#pragma once
#include "include/shaiya/CUser.h"

using namespace shaiya;

namespace packets::items::inventory
{
	void __fastcall send_all(CUser* user);
	void hook();
}