#pragma once
#include <cstdint>

namespace packets
{
	enum struct PacketType : uint16_t
	{
		CharacterList = 0x0101,
		CharacterDetails = 0x0105,
		CharacterItem = 0x0106,
		CheckCharnameAvailable = 0x0119,
		AutoStatsList = 0x0120,
		MoveItem = 0x0204,
		AddItem = 0x0205,
		UpdateItem = 0x0206,
		SortInventoryItems = 0x021F,
		CharacterStatus = 0x0526,
		WarehouseItems = 0x0711,
		LinkResult = 0x0801,
		ExtractResult = 0x0802,
		EnchantResult = 0x0805,
		TradeReceiveItem = 0x0A09,
		GuildWarehouseItemList = 0x0D29,
		GuildWarehouseAddItem = 0x0D31,
		GuildWarehouseRemoveItem = 0x0D32,
		PlayerMarketItems = 0x230B,
		BuyPlayerMarketItem = 0x230D,
		DuelItem = 0x240D,
		Ping = 0xA303,
		AttributeSet = 0xF701
	};

	struct Packet
	{
		PacketType opcode;
		uint8_t data[512];
	};
}
