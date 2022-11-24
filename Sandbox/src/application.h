#include <engine.h>


using namespace ds;
using namespace graphics;
using namespace util;

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
