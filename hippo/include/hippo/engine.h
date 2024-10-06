#include "core/window.h"
#include "managers/logmanager.h"

namespace hippo {

	class Engine {
	public:
		static Engine& Instance();
		~Engine();

		void Run();
		inline void Quit() { mIsRunning = false; }

	private:
		void GetInfo();
		[[nodiscard]] bool Initialize();
		void Shutdown();

	private:
		bool mIsRunning;
		bool mIsInitialized;
		core::Window mWindow;
		
		// managers
		managers::LogManager mLogManager;

		// singleton
		static Engine* mInstance;
		Engine();
	};
}
