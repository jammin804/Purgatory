#pragma once
#include "EString.h"
#include <map>
#include <set>
#include <vector>

class GameObject;
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

	std::vector<int> PayloadInts;
	std::vector<bool> PayloadBools;
	std::vector<float> PayloadFloats;

};

class EventManager 
{
public:
	static void AddEventListener(GameObject*, int);
	static void RemoveEventListener(GameObject*, int);
	static void BroadcastEvent(EventMessage);

private:
	static std::map<int, set<GameObject*>> ListenerMap;
};