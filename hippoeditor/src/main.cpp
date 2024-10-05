#include <iostream>
#include <cstdint>
#include <hippo/engine.h>

using namespace std;

int main()
{ 
	hippo::Engine& engine = hippo::Engine::Instance();
	engine.Run();
	return 0;
}