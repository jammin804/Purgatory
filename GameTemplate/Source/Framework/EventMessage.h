#pragma once
#include <vector>

struct EventPayload;
struct EventMessage
{
	int messageId;

	EventMessage(int);

	bool operator==(EventMessage& Other) const
	{
		return messageId == Other.messageId;
	}

	bool operator==(const EventMessage& Other) const
	{
		return messageId == Other.messageId;
	}

	bool operator==(int Other) const
	{
		return messageId == Other;
	}


	bool operator<(const EventMessage& Other) const
	{
		return messageId < Other.messageId;
	}

	std::vector<EventPayload> payload;

};

struct EventPayload
{
	void SetAsInt(int value);
	void SetAsFloat(float value);
	void SetAsBool(bool value);

	int GetAsInt() const;
	float GetAsFloat() const;
	bool GetAsBool() const;

private:
	float payload;
};