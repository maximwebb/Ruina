#include "Manager.h"
#include "System.h"


void Manager::RegisterEventListener(std::type_index type, EventHandler handler) {
	if (listeners.find(type) == listeners.end()) {
		listeners.emplace(type, std::vector<EventHandler>({std::move(handler)}));
	} else {
		listeners.at(type).emplace_back(handler);
	}
}