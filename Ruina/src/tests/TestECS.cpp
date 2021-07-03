#include "TestECS.h"
#include "Manager.h"
#include "System.h"

class LogEvent : public Event {};

struct MessageComponent : public Component {
	std::string message;
	explicit MessageComponent(std::string msg) : message(std::move(msg)) {};
};

class LoggingSystem : public System {
public:
	LoggingSystem(Manager& m) : System(m) {
		Subscribe<LogEvent>(HANDLER(LogMessages));
	};

	void LogMessages(const Event&) {
		auto group = m.CreateGroup<MessageComponent>();
		for (auto e : group) {
			auto [message_component] = group.Get(e);
			std::cout << message_component->message << std::endl;
		}
	}
};


namespace test {
	TestECS::TestECS() {
		Manager m;
		LoggingSystem logging_system(m);

		Entity e1 = m.Create();
		Entity e2 = m.Create();
		m.Add<MessageComponent>(e1, "This is the first piece of text.");
		m.Add<MessageComponent>(e2, "This is the second piece of text.");
		LogEvent e;
		m.QueueEvent<LogEvent>(e);
		m.QueueEvent<LogEvent>(e);
	}
}