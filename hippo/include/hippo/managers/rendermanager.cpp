#include "log.h"
#include "rendermanager.h"
#include <glad/glad.h>

namespace hippo::managers {
	RenderManager::RenderManager()
	{

	}

	RenderManager::~RenderManager()
	{

	}

	void RenderManager::Initialize()
	{
		HIPPO_INFO("OpenGL Info:\nVendor:{}\nRenderer:{},Version:{}",
			(const char*) glGetString(GL_VENDOR),
			(const char*) glGetString(GL_RENDERER),
			(const char*) glGetString(GL_VERSION));

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(
			static_cast<float>(0x64) / static_cast<float>(0xff),
			static_cast<float>(0x95) / static_cast<float>(0xff),
			static_cast<float>(0xed) / static_cast<float>(0xff),
			1
		);
	}

	void RenderManager::Shutdown()
	{
		while (mRenderCommands.size() > 0)
			mRenderCommands.pop();
	}

	void RenderManager::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void RenderManager::Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> renderCommand)
	{
		mRenderCommands.push(std::move(renderCommand));
	}

	void RenderManager::Clear()
	{
		while (mRenderCommands.size() > 0)
			mRenderCommands.pop();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderManager::Flush()
	{
		while (mRenderCommands.size() > 0) {
			auto rc = std::move(mRenderCommands.front());
			mRenderCommands.pop();
			rc->Execute();
		}
	}
}

