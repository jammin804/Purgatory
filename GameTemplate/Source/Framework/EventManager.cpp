#include "EventManager.h"
#include "GameObject.h"
#include "EventMessage.h"

std::map<int, set<GameObject*>> EventManager::ListenerMap;

void EventManager::AddEventListener(GameObject* GO, int MsgId)
{
	auto iter = ListenerMap.find(MsgId);
	if (iter != ListenerMap.end())
	{
		iter->second.insert(GO);
	}
	else
	{
		auto newEntry = std::make_pair(MsgId, std::set<GameObject*>());
		newEntry.second.insert(GO);
		ListenerMap.insert(newEntry);

	}
}

void EventManager::RemoveEventListener(GameObject* GO, int MsgId)
{
	auto iter = ListenerMap.find(MsgId);
	if (iter != ListenerMap.end())
	{
		iter->second.erase(GO);
		//remove entry from listener map if set is empty
	}
}

void EventManager::BroadcastEvent(const EventMessage& Msg)
{
 	auto iter = ListenerMap.find(Msg.messageId);
	if (iter != ListenerMap.end())
	{
		for (GameObject* GO : iter->second)
		{
			GO->OnEvent(Msg);
		}
	}
}


