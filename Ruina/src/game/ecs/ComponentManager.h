#pragma once
#include <stack>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include "Component.h"
#include "ECS.h"
#include "MeshComponent.h"
#include "MotionComponent.h"

class ComponentManager {
public:
	ComponentManager() : m_components(), m_grouped_components(), m_current_id(0), m_free_ids() {}

	template<typename T, typename... ARGS>
	ComponentId CreateComponent(EntityId entity_id, ARGS&... args) {
		ComponentId id;
		Component* c = nullptr;

		if (m_free_ids.empty()) {
			id = ++m_current_id;
		}
		else {
			id = m_free_ids.top();
			m_free_ids.pop();
		}

		c = new T(id, entity_id, args...);

		if (c != nullptr) {
			if (m_grouped_components.find(typeid(T)) == m_grouped_components.end()) {
				m_grouped_components[typeid(T)] = std::unordered_set<Component*>();
			}
			m_grouped_components[typeid(T)].insert(c);
			m_components.insert({id, c});
		}
		return id;
	}

	template<typename T>
	std::unordered_set<Component*> GetComponentGroup() {
		auto result = m_grouped_components.find(typeid(T));
		if (result == m_grouped_components.end()) {
			throw std::exception("Error: Cannot find component type");
		}
		return result->second;
	}

	template<typename T>
	T* GetComponent(EntityId id) {
		auto components = GetComponentGroup<T>();
		auto result = std::find_if(components.begin(), components.end(), [id](Component* x){return x->m_entity_id == id;});
		if (result == components.end()) {
			throw std::exception("Error: Cannot find component type");
		}
		return (T*)*result;
	}

	Component* GetComponent(ComponentId id) {
		auto result = m_components.find(id);
		if (result == m_components.end()) {
			throw std::exception("Error: Cannot find component");
		}
		return result->second;
	}

	void DestroyComponent(ComponentId id) {
		Component* c = m_components.find(id)->second;
		std::unordered_set<Component*>& group1 = m_grouped_components.at(typeid(MeshComponent));
		group1.erase(c);
		m_components.erase(id);
		auto group = GetComponentGroup<MeshComponent>();
		m_free_ids.push(id);
		delete c;
	}

private:
	std::unordered_map<ComponentId, Component*> m_components;
	std::unordered_map<std::type_index, std::unordered_set<Component*>> m_grouped_components;
	ComponentId m_current_id;
	std::stack<ComponentId> m_free_ids;
};