#pragma once
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "Event.h"
#include "../ecs/ECSTypes.h"

enum class EventType;
class System;

class EventManager {
public:
	EventManager();
	~EventManager();
	void RegisterListener(SystemId, EventType);
	void UnregisterListener(SystemId, EventType);
	void NotifyListeners();

	template<typename T>
	void QueueEvent() {
		Event* e = static_cast<Event*>(new T());
		m_events_queue.emplace(e);
	}

private:
	std::priority_queue<Event*> m_events_queue;
	std::unordered_map<EventType, std::unordered_set<SystemId>> m_listeners;
};