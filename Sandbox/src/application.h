#include <engine.h>

using namespace ds;
using namespace graphics;
using namespace util;

class Application
{
private:
	graphics::Window* window;
	
	OrthographicCamera* camera;

	Texture* block;
	Texture* wall;
	Texture* entryDoor;
	Texture* exitDoor;

	Tilemap* tilemap;

public:
	Application();

	void Setup();
	void Update();
	void HandleInput();
	void Run();
};
