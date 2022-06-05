#pragma once
#include "EString.h"
#include <map>
#include <set>

class GameObject;
struct EventMessage;
class EventManager 
{
public:
	void AddEventListener(GameObject*, EventMessage);
	void RemoveEventListener(GameObject*, EventMessage);
	void BroadcastEvent(EventMessage);

private:
	std::map<EventMessage, set<GameObject*>> ListenerMap;
};

struct EventMessage
{
	int messageId;

	EventMessage(int);

	bool operator==(EventMessage& Other) const
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

};

static EventManager EvtManager;