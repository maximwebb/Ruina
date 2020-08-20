#pragma once
#include "../events/Event.h"
#include "ECSTypes.h"

class System {
public:
	System(SystemId id) : m_id(id) {};
	~System() {
	}

	void SubscribeToEvent(EventType);

	virtual void Update(const Event& e) = 0;
public:
	SystemId m_id;
};

class LoggingSystem : public System {
public:
	LoggingSystem(SystemId);

	void Update(const Event& e) override;
};