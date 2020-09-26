#pragma once
#include "ECS.h"
#include "Event.h"

class System {
public:
	System(SystemId id) : m_id(id) {};
	~System() {
	}

	template<typename T>
	void SubscribeToEvent() {
		static_assert(std::is_base_of<Event, T>::value, "Error: invalid event type");
		ECSEngine::event_manager().RegisterListener<T>(m_id);
	}

	virtual void Update(const Event& e) = 0;
public:
	SystemId m_id;
};

class LoggingSystem : public System {
public:
	LoggingSystem(SystemId);

	void Update(const Event& e) override;
};