#pragma once
#include <queue>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "ECS.h"
#include "Event.h"

class System;

class EventManager {
public:
	EventManager() = default;
	~EventManager() = default;

	template<typename T>
	void RegisterListener(SystemId id) {
		static_assert(std::is_base_of<Event, T>::value, "Error: invalid event type");
		if (m_listeners.find(typeid(T)) == m_listeners.end()) {
			m_listeners[typeid(T)] = std::unordered_set<SystemId>();
		}
		m_listeners[typeid(T)].insert(id);
	}

	template<typename T>
	void UnregisterListener(SystemId id) {
		static_assert(std::is_base_of<Event, T>::value, "Error: invalid event type");
		m_listeners[typeid(T)].erase(id);
	};

	template<typename T>
	void QueueEvent() {
		static_assert(std::is_base_of<Event, T>::value, "Error: invalid event type");
		T e;
		m_events_queue.emplace(e, typeid(T));
	}

	void NotifyListeners();

private:
	//std::priority_queue<std::pair<Event, std::type_index>, std::vector<std::pair<Event, std::type_index>>, LowerPriority> m_events_queue;
	std::queue<std::pair<Event, std::type_index>> m_events_queue;
	std::unordered_map<std::type_index, std::unordered_set<SystemId>> m_listeners;
};