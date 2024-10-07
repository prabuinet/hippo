#include "graphics/helpers.h"

namespace hippo::graphics {

	void CheckGLErrors()
	{
		GLenum error = glGetError();
		bool shouldAssert = error != GL_NO_ERROR;

		while (error != GL_NO_ERROR) {
			std::string error_str;
			switch (error) {
			case GL_INVALID_OPERATION: error_str = "GL_INVALID_OPERATION"; break;
			case GL_INVALID_ENUM: error_str = "GL_INVALID_ENUM"; break;
			case GL_INVALID_VALUE: error_str = "GL_INVALID_VALUE"; break;
			case GL_OUT_OF_MEMORY: error_str = "GL_OUT_OF_MEMORY"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: error_str = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
			default:
				error_str = std::to_string(error);
				break;
			}

			HIPPO_ERROR("OpenGL Error: {}", error_str.c_str());
			error = glGetError();
		}

		HIPPO_ASSERT(!shouldAssert, "OpenGL Error!");
	}
}