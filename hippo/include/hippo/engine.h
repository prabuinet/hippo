#include "core/window.h"

namespace hippo {

	class Engine {
	public:
		static Engine& Instance();
		~Engine();

		void Run();
		inline void Quit() { mIsRunning = false; }

	private:
		Engine();
		
		void GetInfo();
		[[nodiscard]] bool Initialize();
		void Shutdown();

		static Engine* mInstance;
		core::Window mWindow;
		bool mIsRunning;
	};
}
