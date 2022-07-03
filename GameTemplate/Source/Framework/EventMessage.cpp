#include "EventMessage.h"

EventMessage::EventMessage(int MsgId)
{
	messageId = MsgId;
}

void EventPayload::SetAsInt(int value)
{
	payload = static_cast<float>(value);
}

void EventPayload::SetAsFloat(float value)
{
	payload = value;

}

void EventPayload::SetAsBool(bool value)
{
	payload = static_cast<float>(value);

}

int EventPayload::GetAsInt() const
{
	return static_cast<int>(payload);
}

float EventPayload::GetAsFloat() const
{
	return payload;
}

bool EventPayload::GetAsBool() const
{
	return static_cast<bool>(payload);
}
