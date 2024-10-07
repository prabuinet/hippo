#pragma once

#include <cstdint>

namespace hippo::graphics {
	class Mesh {
	public:
		Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions);
		~Mesh();

		void Bind();
		void Unbind();

		inline uint64_t GetVertexCount() const { return mVertexCount; }

	private:
		uint64_t mVertexCount;
		uint32_t mVao;
		uint32_t mPositionVbo;
	};
}