#include "EventManager.h"
#include "ECSEngine.h"

class SystemManager;

EventManager::EventManager() {
	for (int i = 0; i != (int)EventType::END; i++) {
		m_listeners[(EventType)i] = std::unordered_set<SystemId>();
	}
}

EventManager::~EventManager() {

}

void EventManager::RegisterListener(SystemId id, EventType type) {
	m_listeners[type].insert(id);
}

void EventManager::UnregisterListener(SystemId id, EventType type) {
	m_listeners[type].erase(id);
}

void EventManager::NotifyListeners() {
	Event* e;
	while (!m_events_queue.empty()) {
		e = m_events_queue.top();
		for (SystemId id : m_listeners[e->GetEventType()]) {
			ECSEngine::system_manager().GetSystem(id).Update(*e);
		}
		m_events_queue.pop();
	}
}
