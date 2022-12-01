#include <engine.h>

using namespace ds;
using namespace graphics;
using namespace util;

class Application
{
private:
	graphics::Window* window;

	Text* text;

public:
	Application();
	~Application();

	void Setup();
	void Update();
	void HandleInput();
	void Run();
};
