#pragma once

#include "log.h"
#include "glad/glad.h"

namespace hippo::graphics {

	void CheckGLErrors();
}

#ifndef HIPPO_CONFIG_RELEASE
#define HIPPO_CHECK_GL_ERROR hippo::graphics::CheckGLErrors();
#else
#define HIPPO_CHECK_GL_ERROR (void)0;
#endif
