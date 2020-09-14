#include "EventManager.h"
#include "ECSEngine.h"

class SystemManager;

void EventManager::NotifyListeners() {
	Event event;
	while (!m_events_queue.empty()) {
		event = m_events_queue.front().first;
		std::type_index event_type = m_events_queue.front().second;
		auto foo = m_listeners[event_type];
		for (SystemId id : m_listeners[event_type]) {
			ECSEngine::system_manager().GetSystem(id)->Update(event);
		}
		m_events_queue.pop();
	}
}
