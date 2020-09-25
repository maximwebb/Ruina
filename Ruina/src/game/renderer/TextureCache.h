#pragma once
#include <list>
#include <unordered_map>
#include "Texture.h"

class TextureCache {
public:
	TextureCache(int N)
		: m_list(0), m_map(N), m_size(0), m_capacity(N) {};

	int Bind(const Texture& texture) {
		std::string key = texture.m_filepath;
		auto res = m_map.find(key);
		if (res == m_map.end()) {
			if (m_size < m_capacity) {
				std::pair<int, std::string>* ptr = &*m_list.insert(m_list.end(), {m_size, key});
				m_map.insert({key, ptr});

				texture.Bind(m_size);
				return m_size++;
			}
			else {
				std::pair<int, std::string> pair = m_list.front();
				m_list.pop_front();
				int slot = pair.first;
				std::string old_key = pair.second;
				std::pair<int, std::string>* ptr = &*m_list.insert(m_list.end(), {slot, key});
				m_map.erase(old_key);
				m_map.insert({key, ptr});

				texture.Bind(slot);
				return slot++;
			}
		}
		else {
			auto* pair = new std::pair<int, std::string>(*res->second);
			m_list.remove(*pair);
			m_map.erase(pair->second);
			m_list.push_back(*pair);
			m_map.insert({std::string(pair->second), pair});

			return pair->first;
		}
	}
private:
	std::list<std::pair<int, std::string>> m_list;
	std::unordered_map<std::string, std::pair<int, std::string>*> m_map;
	int m_size;
	int m_capacity;
};