#include <engine.h>

using namespace ds;
using namespace graphics;
using namespace maths;
using namespace util;

class Application
{
private:
	graphics::Window* window;
	
	Sprite* sprite;
	
	Music* music;
	SoundEffect* sf;

public:
	Application();
	~Application();

	void Setup();
	void Update();
	void HandleInput();
	void Run();
};
