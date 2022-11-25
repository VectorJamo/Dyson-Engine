#include <engine.h>

using namespace ds;
using namespace graphics;
using namespace util;

class Application
{
private:
	graphics::Window* window;
	
	OrthographicCamera* camera;

	Sprite* sprite;

public:
	Application();

	void Setup();
	void Update();
	void HandleInput();
	void Run();
};
