#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <numeric>
#include <vector>
#include "Manager.h"
#include "TextureManager.h"
#include "MeshComponent.h"
#include "VertexPNUV.h"

class MeshComponentFactory {
public:
	MeshComponentFactory(Manager& m) : m(m) {};

	Component& CreateCubeMesh(Entity id, glm::mat4 model) {
		Texture& cube_texture = TextureManager::Get("Ruina/res/textures/texture_palette.png");
		std::vector cube_vertices = CubeMesh();
		std::vector cube_indices = CubeIndices();
		return m.Add<MeshComponent>(id, cube_vertices, cube_indices, cube_texture, model);
	}

	Component& CreateCubeMesh(Entity id, float x, float y, float z) {
		glm::mat4 model = glm::translate(
				glm::scale(
						glm::rotate(
								glm::mat4(1.0f),
								0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
						glm::vec3(2.0f, 2.0f, 2.0f)),
				glm::vec3(x, y, z));
		return CreateCubeMesh(id, model);
	}

	const Component& CreateOctahedronMesh(Entity id, glm::mat4 model) {
		std::vector<VertexPNUV> vertices = OctahedronMesh();
		std::vector<unsigned int> indices(24);
		std::iota(std::begin(indices), std::end(indices), 0);
		Texture& texture = TextureManager::Get("Ruina/res/textures/rainbow.png");
		return m.Add<MeshComponent>(id, vertices, indices, texture, model);
	}

	const Component& CreateSphereMesh(Entity id, glm::mat4 model, int depth) {
		std::vector<VertexPNUV> sphere_vertices;

		std::vector<VertexPNUV> octahedron_vertices = OctahedronMesh();
		std::vector<VertexPNUV> tessellated_vertices;
		for (int i = 0; i < octahedron_vertices.size(); i += 3) {
			VertexPNUV v1 = octahedron_vertices.at(i);
			VertexPNUV v2 = octahedron_vertices.at(i + 1);
			VertexPNUV v3 = octahedron_vertices.at(i + 2);

			glm::vec3 v1_pos = glm::vec3(v1.x, v1.y, v1.z);
			glm::vec3 v2_pos = glm::vec3(v2.x, v2.y, v2.z);
			glm::vec3 v3_pos = glm::vec3(v3.x, v3.y, v3.z);

			std::vector<VertexPNUV> vertices = TessellateTriangle(v1_pos, v2_pos, v3_pos, depth);
			for (VertexPNUV& vertex : vertices) {
				glm::vec3 normalized_pos = glm::normalize(glm::vec3(vertex.x, vertex.y, vertex.z));
				vertex.x = normalized_pos.x;
				vertex.y = normalized_pos.y;
				vertex.z = normalized_pos.z;

				vertex.n_x = normalized_pos.x;
				vertex.n_y = normalized_pos.y;
				vertex.n_z = normalized_pos.z;
				float PI = 3.14159265f;
//				float theta = acos(normalized_pos.z)/PI;
//				float phi = (atan(normalized_pos.y/normalized_pos.x) + PI/2)/PI;
				float theta = (atan(normalized_pos.x / normalized_pos.z) + PI / 2) / (1.5 * PI);;
				float phi = (normalized_pos.y + 1) / 2;

				vertex.u = theta;
//				vertex.v = 0.5;
				vertex.v = phi;
			}
			sphere_vertices.insert(sphere_vertices.end(), vertices.begin(), vertices.end());
		}
		std::vector<unsigned int> sphere_indices(sphere_vertices.size());
		Texture& sphere_texture = TextureManager::Get("Ruina/res/textures/basketball.png");
		std::iota(std::begin(sphere_indices), std::end(sphere_indices), 0);
		return m.Add<MeshComponent>(id, sphere_vertices, sphere_indices, sphere_texture, model);
	}


	static std::vector<VertexPNUV> TessellateTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, int depth) {
		std::vector<VertexPNUV> vertices;
		int width = 2 * depth - 1;
		int height = depth;

		glm::vec3 e1 = (1.0f / (float) depth) * (v2 - v1);
		glm::vec3 e2 = (1.0f / (float) depth) * (v3 - v1);
		glm::vec3 pos = v1;
		glm::vec3 normal = glm::normalize(glm::cross(e1, e2));
		for (int i = 0; i < height; i++) {
			bool up = true;
			pos = v1 + (float) i * e2;
			for (int j = 0; j < width; j++) {
				if (up) {
					vertices.emplace_back(pos, normal, glm::vec2(0, 0));
					vertices.emplace_back(pos + e1, normal, glm::vec2(0.333f, 0));
					vertices.emplace_back(pos + e2, normal, glm::vec2(0, 0.5f));
					pos += e1;
				} else {
					vertices.emplace_back(pos, normal, glm::vec2(0.333f, 0));
					vertices.emplace_back(pos + e2, normal, glm::vec2(0.333f, 0.5f));
					vertices.emplace_back(pos - e1 + e2, normal, glm::vec2(0, 0.5f));
				}
				up = !up;
			}
			width -= 2;
		}
		return vertices;
	}

	static std::vector<VertexPNUV> CubeMesh() {
		std::vector<VertexPNUV> vertices;
		vertices.reserve(24);
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.333f, 0.0f));
		vertices.emplace_back(VertexPNUV(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.333f, 0.5f));
		vertices.emplace_back(VertexPNUV(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f));

		vertices.emplace_back(VertexPNUV(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.667f, 0.0f));
		vertices.emplace_back(VertexPNUV(1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.333f, 0.0f));
		vertices.emplace_back(VertexPNUV(1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.667f, 0.5f));
		vertices.emplace_back(VertexPNUV(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.333f, 0.5f));

		vertices.emplace_back(VertexPNUV(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.667f, 0.0f));
		vertices.emplace_back(VertexPNUV(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f));
		vertices.emplace_back(VertexPNUV(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.667f, 0.5f));

		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.333f, 0.5f));
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.5f));
		vertices.emplace_back(VertexPNUV(0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.333f, 1.0f));
		vertices.emplace_back(VertexPNUV(0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f));

		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.667f, 0.5f));
		vertices.emplace_back(VertexPNUV(1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.333f, 0.5f));
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.667f, 1.0f));
		vertices.emplace_back(VertexPNUV(1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.333f, 1.0f));

		vertices.emplace_back(VertexPNUV(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f));
		vertices.emplace_back(VertexPNUV(1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.667f, 0.5f));
		vertices.emplace_back(VertexPNUV(0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f));
		vertices.emplace_back(VertexPNUV(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.667f, 1.0f));

		return vertices;
	}

	static std::vector<unsigned int> CubeIndices() {
		std::vector<unsigned int> cube_indices = {
				0, 1, 2,
				2, 1, 3,

				4, 5, 6,
				6, 5, 7,

				8, 9, 10,
				10, 9, 11,

				12, 13, 14,
				14, 13, 15,

				16, 17, 18,
				18, 17, 19,

				20, 21, 22,
				22, 21, 23
		};
		return cube_indices;
	}

	static std::vector<VertexPNUV> TriangleMesh() {
		std::vector<VertexPNUV> vertices;
		vertices.reserve(3);
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.333f, 0.0f));
		vertices.emplace_back(VertexPNUV(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.1667f, 0.5f));

		return vertices;
	}

	static std::vector<unsigned int> TriangleIndices() {
		std::vector<unsigned int> triangle_indices = {
			0, 1, 2,
		};
		return triangle_indices;
	}

	static std::vector<VertexPNUV> OctahedronMesh() {
		std::vector<VertexPNUV> vertices;
		vertices.reserve(24);

		float normal = 1.0f / sqrt(3);

		// FUL
		vertices.emplace_back(VertexPNUV(-1.0f, 0.0f, 0.0f, -normal, normal, normal, 0.0f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, -1.0f, -normal, normal, normal, 0.333f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, 1.0f, 0.0f, -normal, normal, normal, 0.333f, 0.5f));

		// FUR
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, -1.0f, normal, normal, normal, 0.333f, 0.0f));
		vertices.emplace_back(VertexPNUV(1.0f, 0.0f, 0.0f, normal, normal, normal, 0.667f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, 1.0f, 0.0f, normal, normal, normal, 0.667f, 0.5f));

		// FDL
		vertices.emplace_back(VertexPNUV(-1.0f, 0.0f, 0.0f, -normal, -normal, normal, 0.333f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, -1.0f, 0.0f, -normal, -normal, normal, 0.667f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, -1.0f, -normal, -normal, normal, 0.667f, 0.5f));

		// FDR
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, -1.0f, normal, -normal, normal, 0.0f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, -1.0f, 0.0f, normal, -normal, normal, 0.333f, 0.0f));
		vertices.emplace_back(VertexPNUV(1.0f, 0.0f, 0.0f, normal, -normal, normal, 0.333f, 0.5f));

		// BUL
		vertices.emplace_back(VertexPNUV(-1.0f, 0.0f, 0.0f, -normal, normal, -normal, 0.333f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, 1.0f, 0.0f, -normal, normal, -normal, 0.667f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, 1.0f, -normal, normal, -normal, 0.667f, 0.5f));

		// BUR
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, 1.0f, normal, normal, -normal, 0.0f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, 1.0f, 0.0f, normal, normal, -normal, 0.333f, 0.5f));
		vertices.emplace_back(VertexPNUV(1.0f, 0.0f, 0.0f, normal, normal, -normal, 0.333f, 0.0f));

		// BDL
		vertices.emplace_back(VertexPNUV(-1.0f, 0.0f, 0.0f, -normal, -normal, -normal, 0.0f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, 1.0f, -normal, -normal, -normal, 0.333f, 0.5f));
		vertices.emplace_back(VertexPNUV(0.0f, -1.0f, 0.0f, -normal, -normal, -normal, 0.333f, 0.0f));

		// BDR
		vertices.emplace_back(VertexPNUV(0.0f, 0.0f, 1.0f, normal, -normal, -normal, 0.333f, 0.0f));
		vertices.emplace_back(VertexPNUV(1.0f, 0.0f, 0.0f, normal, -normal, -normal, 0.667f, 0.0f));
		vertices.emplace_back(VertexPNUV(0.0f, -1.0f, 0.0f, normal, -normal, -normal, 0.667f, 0.5f));

		return vertices;
	}

	const Component& TessellatedTriangleMesh(Entity id, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, int depth) {
		std::vector<VertexPNUV> vertices = TessellateTriangle(v1, v2, v3, depth);
		std::vector<unsigned int> indices(vertices.size());
		std::iota(std::begin(indices), std::end(indices), 0);
		Texture& texture = TextureManager::Get("Ruina/res/textures/rainbow.png");

		glm::mat4 model(1);
		return m.Add<MeshComponent>(id, vertices, indices, texture, model);
	}

private:
	Manager& m;

};
