#pragma once

#include <cstdint>

namespace hippo::graphics {
	class Mesh {
	public:
		Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions);
		~Mesh();

		void Bind();
		void Unbind();

	private:
		uint32_t mVertexCount;
		uint32_t mVao;
		uint32_t mPositionVbo;

	};
}