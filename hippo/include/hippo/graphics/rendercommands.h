#pragma once

namespace hippo::graphics::rendercommands {

	class RenderCommand {
	public:
		virtual void Execute() = 0;
		virtual ~RenderCommand() { }
	};

}