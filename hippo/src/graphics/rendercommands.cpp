#include "graphics/rendercommands.h"
#include "log.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"

namespace hippo::graphics::rendercommands
{
	RenderCommand::~RenderCommand() 
	{

	}

	void RenderMesh::Execute() {
		std::shared_ptr<Mesh> mesh = mMesh.lock();
		std::shared_ptr<Shader> shader = mShader.lock();

		if (mesh && shader) {
			mesh->Bind();
			shader->Bind();

			glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(mesh->GetVertexCount()));

			shader->Unbind();
			mesh->Unbind();
		}
		else {
			HIPPO_WARN("attempting to execute rendermesh with invlalid data");
		}
	}
}
