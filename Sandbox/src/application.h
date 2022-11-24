#include <engine.h>

using namespace ds;

class Application
{
private:
	graphics::Window* window;

public:
	Application();

	void Setup();
	void Update();
	void Run();

};
