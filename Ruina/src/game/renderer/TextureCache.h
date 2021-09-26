#pragma once
#include <list>
#include <unordered_map>
#include "Texture.h"

class TextureCache {
public:
	TextureCache(int size)
		: cache(0), map(size), cache_size(0), capacity(size) {};

	int Bind(const Texture& texture) {
		std::string key = texture.path;
		auto res = map.find(key);
		if (res == map.end()) {
			// If there's space, insert directly into map, and insert into list (cache) at the next slot position
			if (cache_size < capacity) {
				std::pair<int, std::string> pair = *cache.insert(cache.end(), {cache_size, key});
				map.insert({key, pair});
				texture.Bind(cache_size);
				return cache_size++;
			}
			// Otherwise, remove the element at the front of the list (noting its texture slot), and insert at the end.
			else {
				std::pair<int, std::string> old_pair = cache.front();
				cache.pop_front();
				int slot = old_pair.first;
				std::string old_key = old_pair.second;
				std::pair<int, std::string> pair = *cache.insert(cache.end(), {slot, key});
				map.erase(old_key);
				map.insert({key, pair});
				texture.Bind(slot);
				return slot;
			}
		}
		// If cache hit, move element to back of list.
		else {
			auto pair = std::pair<int, std::string>(res->second);
			cache.remove(pair);
			map.erase(pair.second);
			cache.push_back(pair);
			map.insert({std::string(pair.second), pair});
			texture.Bind(pair.first);
			return pair.first;
		}
	}

private:
	std::list<std::pair<int, std::string>> cache;
	std::unordered_map<std::string, std::pair<int, std::string>> map;
	int cache_size;
	int capacity;
};