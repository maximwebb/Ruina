#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>
#include "Component.h"
#include "Entity.h"
#include "Event.h"
#include "Group.h"
#include "System.h"


class Manager {
private:
	class TypeKey {
	public:
		uint64_t key;

		TypeKey() : key(0) {};

		void Add(int type_id) {
			key |= (1 << type_id);
		}

		void Remove(int type_id) {
			key &= !(1 << type_id);
		}

		bool Contains(uint64_t type) const {
			if ((key & type) > 0) {
				return true;
			} else {
				return false;
			}
		}

		bool Contains(const TypeKey& other) const {
			return (other.key & key) == other.key;
		}

		bool operator==(const TypeKey& other) const {
			return other.key == key;
		}

		explicit operator uint64_t() const {
			return key;
		}
	};

	typedef std::function<void(const Event&)> EventHandler;

	std::unordered_map<std::type_index, std::vector<Component*>> components;
	std::vector<Entity> entities;
	// Store mapping between entity_tuples, and lists of components (and their corresponding type ids)
public:
	std::unordered_map<int32_t, std::vector<std::pair<int, Component*>>> component_bags;

	uint64_t next_entity_id;
	int next_type_id;

	std::unordered_map<std::type_index, int> type_ids;
	std::unordered_map<int32_t, TypeKey> type_keys;
	std::unordered_map<TypeKey, std::hash<uint64_t>, Group<>*> groups;
	std::unordered_map<std::type_index, std::vector<EventHandler>> listeners;

public:
	Manager()
			: components(std::unordered_map<std::type_index, std::vector<Component*>>()),
			  entities(std::vector<Entity>()),
			  component_bags(std::unordered_map<int32_t, std::vector<std::pair<int, Component*>>>()),
			  next_entity_id(0),
			  next_type_id(0),
			  type_ids(std::unordered_map<std::type_index, int>()),
			  type_keys(std::unordered_map<int32_t, TypeKey>()),
			  groups(std::unordered_map<TypeKey, std::hash<uint64_t>, Group<>*>()) {}

	const Entity& Create() {
		auto& e = entities.emplace_back(next_entity_id);
		component_bags.emplace(e, std::vector<std::pair<int, Component*>>());
		type_keys[e] = TypeKey();
		next_entity_id++;
		return e;
	}

	void Delete(Entity e) {
		auto bag = component_bags.at(e);
		for (auto& [type, component] : bag) {
			int t = type;
			auto result = std::find_if(
			  type_ids.begin(),
			  type_ids.end(),
			  [t](const auto& el) {return el.second == t; });
			std::type_index key = result->first;
			auto list = components.at(key);
			list.erase(std::remove(list.begin(), list.end(), component), list.end());
			delete component;
		}
		entities.erase(std::remove(entities.begin(), entities.end(), e), entities.end());
	}

	template<class T, typename... ARGS>
	Component& Add(Entity e, const ARGS& ... args) {
		T* c = new T(args...);
		c->entity_id = e.id;
		std::type_index type = typeid(T);
		if (components.find(type) == components.end()) {
			components.emplace(type, std::vector<Component*>());
			type_ids.emplace(type, next_type_id);
			next_type_id++;
		}
		components.at(typeid(T)).emplace_back(c);
		component_bags.at(e).emplace_back(type_ids.at(type), c);

		/* Update entity's typekey to include new component */
		int type_id = type_ids.at(type);
		type_keys.at(e).Add(type_id);

		return *c;
	}

	/* Template code to recursively generate tuple of components */
	template<int N, class T, class... Ts>
	std::tuple<T*, Ts* ...> InitialiseTuple(const std::vector<Component*>& bases) {
		std::tuple<Ts* ...> tuple = InitialiseTuple<N + 1, Ts...>(bases);
		T* t = static_cast<T*>(bases.at(N));
		std::tuple<T*> current = std::tie(t);
		return std::tuple_cat(current, tuple);
	}

	template<int>
	std::tuple<> InitialiseTuple(const std::vector<Component*>& bases) {
		return std::tuple<>();
	}

	template<class... T>
	Group<T* ...>& CreateGroup() {
		std::vector<std::type_index> types = {typeid(T)...};
		TypeKey key;
		auto group = new Group<T* ...>();

		/* Create typekey for group, and ensure all necessary types are initialised */
		for (std::type_index type : types) {
			key.Add(type_ids[type]);
			if (components.find(type) == components.end()) {
				components.emplace(type, std::vector<Component*>());
				type_ids.emplace(type, next_type_id);
				next_type_id++;
			}
		}

		/* Iterate through entity_tuples with a matching typekey, and locate all components required to generate tuple */
		for (Entity e : entities) {
			TypeKey& type_key = type_keys.at(e);
			if (type_key.Contains(key)) {
				auto component_bag = component_bags.at(e);
				std::vector<Component*> cs;
				for (std::type_index type : types) {
					int type_id = type_ids.at(type);
					for (auto [id, component] : component_bag) {
						if (id == type_id) {
							cs.push_back(component);
							break;
						}
					}
				}
				std::tuple<T* ...> tuple = InitialiseTuple<0, T...>(cs);
				group->Push(e, tuple);
			}
		}

		return *group;
	}


	void RegisterEventListener(std::type_index type, EventHandler handler);


	template<typename T>
	void QueueEvent(const T& e) {
		static_assert(std::is_base_of<Event, T>::value);
		std::type_index type_id = typeid(e);
		if (listeners.find(type_id) != listeners.end()) {
			for (const auto& handler : listeners.at(type_id)) {
				handler(e);
			}
		}
	}


	void PrintEntities() {
		for (Entity e : entities) {
			std::cout << e.id << std::endl;
		}
	}

	template<typename T>
	void PrintComponents() {
		std::type_index type_index = typeid(T);
		if (components.find(type_index) != components.end()) {
			for (Component* c : components.at(type_index)) {
				T* c1 = static_cast<T*>(c);
				c1->Print();
			}
		}
	}
};