#pragma once
#include "Game.h"
#include "../geometry/Cube.h"
#include <unordered_map>

struct LocationKey {
	unsigned int x, y, z;

	bool operator== (const LocationKey& o) const {
		return (x==o.x) && (y==o.y) && (z==o.z);
	}
};

struct LocationHash {
	std::size_t operator() (const LocationKey& o) const {
		return std::hash<int>()(o.x) ^ std::hash<int>()(o.y) ^ std::hash<int>()(o.z);
	}
};

class Chunk {
public:
	Chunk(unsigned int size);
	~Chunk() = default;
	Cube& GetCube(unsigned int, unsigned int, unsigned int);
	void SetCube(unsigned int, unsigned int, unsigned int);
	void GenerateRenderingData();
public:
	const unsigned int m_size;
	int m_cubes_count;
	std::vector<float> m_vertex_data;
	int m_vertex_data_size;
	std::vector<unsigned int> m_index_data;
	int m_index_data_size;
private:
	std::unordered_map<LocationKey, Cube, LocationHash> m_cubes;
};