#pragma once
#include <cstdint>
#include <functional>
#include <iostream>
#include <typeindex>
#include <utility>

#define HANDLER(func) [this](auto&& e) { func(std::forward<const Event&>(e)); }

class Manager;

class System {
public:
    typedef std::function<void(const Event&)> EventHandler;
    int32_t id;
    Manager& m;

    explicit System(Manager&);

    template<typename T>
	void Subscribe(EventHandler handler) {
		std::type_index type_id = typeid(T);
		SubscribeInner(type_id, std::move(handler));
	}

	void SubscribeInner(std::type_index type_id, EventHandler f);

    virtual void Update(Event e) {
        std::cout << "Received event in base class" << std::endl;
    }

private:
    int getNextId() {
        static int next_id = 0;
        return next_id++;
    }
};
