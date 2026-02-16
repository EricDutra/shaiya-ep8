#include "include/packets/character/attribute.h"

namespace packets::character::attribute
{
	void send(CUser* user, uint8_t attribute_id, uint32_t attribute)
	{
		AttributePacket attribute_packet{};
		attribute_packet.id = attribute_id;
		attribute_packet.attribute = attribute;
		user->Send((void*)&attribute_packet, sizeof(AttributePacket));
	}
}