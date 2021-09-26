#pragma once
#include <fstream>
#include <vector>
#include <sstream>
#include "VertexPNUV.h"

class MeshLoader {
public:
	static std::vector<VertexPNUV> LoadMesh(const char* path) {
		std::vector<VertexPNUV> vertices;
		std::ifstream f(path);
		std::string line;

		std::cout << ParseName(f) << std::endl;

		int max = 25000;
		int i = 0;
		while(f.peek() != EOF && i < max) {
			ParseTriangle(f, vertices);
			i++;
		}
		return vertices;
	}

private:
	static std::string ParseName(std::ifstream& f) {
		std::string line;
		std::getline(f, line);
		std::istringstream iss(line);
		std::string tmp, name;

		if (!(iss >> tmp >> name) || tmp != "solid") {
			return "ERROR";
		} else {
			return name;
		}
	}

	static bool ParseTriangle(std::ifstream& f, std::vector<VertexPNUV>& vertices) {
		std::string line;
		std::string tmp1, tmp2;
		glm::vec3 normal;
		glm::vec3 pos;
//		glm::vec2 uv = {0.0f, 0.0f};
		std::getline(f, line);
		std::istringstream iss(line);
		if (iss >> tmp1 >> tmp2) {
			if (tmp1 == "endsolid") {
				return true;
			} else if (tmp1 == "facet" && tmp2 == "normal") {
				iss >> normal.x >> normal.y >> normal.z;
			}
		} else {
			std::cout << "ERROR parsing triangle" << std::endl;
			return false;
		}

		while (std::getline(f, line)) {
			iss = std::istringstream(line);
			if (iss >> tmp1) {
				if (tmp1 == "outer") {
					iss >> tmp2;
					assert(tmp2 == "loop");
				} else if (tmp1 == "vertex") {
					iss >> pos.x >> pos.y >> pos.z;
					glm::vec2 uv = {glm::acos(pos.z/glm::length(pos)), glm::atan(pos.y/pos.x)};
					vertices.emplace_back(pos, normal, uv);
				} else if (tmp1 == "endloop") {
					std::getline(f, line);
					iss = std::istringstream(line);
					iss >> tmp1;
					assert(tmp1 == "endfacet");
					return true;
				} else {
					return false;
				}
			}
		}
		return false;
	}
};