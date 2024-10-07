#pragma once

#include "graphics/rendercommands.h"
#include <queue>
#include <memory>

namespace hippo::managers {

	class RenderManager {
	public:

		RenderManager();
		~RenderManager();

		void Initialize();
		void Shutdown();

		void SetClearColor(float r, float g, float b, float a);

		void Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> renderCommand);

		void Clear();
		// executes submitted render commands in the order they were received.
		// we can extend the API if we need to mitigate performance impact.
		void Flush();
	private:
		std::queue<std::unique_ptr<graphics::rendercommands::RenderCommand>> mRenderCommands;
	};
}