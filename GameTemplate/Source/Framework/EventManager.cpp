#include "EventManager.h"
#include "GameObject.h"



void EventManager::AddEventListener(GameObject* GO, EventMessage Msg)
{
	auto iter = ListenerMap.find(Msg);
	if (iter != ListenerMap.end())
	{
		iter->second.insert(GO);
	}
	else
	{
		auto newEntry = std::make_pair(Msg, std::set<GameObject*>());
		newEntry.second.insert(GO);
		ListenerMap.insert(newEntry);

	}
}

void EventManager::RemoveEventListener(GameObject* GO, EventMessage Msg)
{
	auto iter = ListenerMap.find(Msg);
	if (iter != ListenerMap.end())
	{
		iter->second.erase(GO);
		//remove entry from listener map if set is empty
	}
}

void EventManager::BroadcastEvent(EventMessage Msg)
{
	auto iter = ListenerMap.find(Msg);
	if (iter != ListenerMap.end())
	{
		for (GameObject* GO : iter->second)
		{
			GO->OnEvent(iter->first);
		}
	}
}

EventMessage::EventMessage(int MsgId)
{
	messageId = MsgId;
}
