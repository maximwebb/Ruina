#pragma once

enum class EventType {
	OnLogRequest, END
};

class Event {
public:
	virtual EventType GetEventType() = 0;
};

class EventOnLogRequest : public Event {
public:
	EventType GetEventType() override {
		return EventType::OnLogRequest;
	}
};