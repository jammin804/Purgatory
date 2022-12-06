#pragma once
#include "EString.h"
#include <map>
#include <set>
#include <vector>

class GameObject;
struct EventMessage;

class EventManager 
{
public:
	static void AddEventListener(GameObject*, int);
	static void RemoveEventListener(GameObject*, int);
	static void BroadcastEvent(const EventMessage&);

private:
	static std::map<int, set<GameObject*>> ListenerMap;
};

//namespace EventManager *Learning Purposing*
//{
//	void AddEventListener(GameObject*, int);
//	void RemoveEventListener(GameObject*, int);
//	void BroadcastEvent(const EventMessage&);
//
//}