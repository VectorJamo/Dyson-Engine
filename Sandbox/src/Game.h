#include <application.h>

using namespace ds;
using namespace graphics;
using namespace util;

class Game : public Application
{
private:
	graphics::Sprite* sprite;

public:
	Game();
	~Game();

	void Setup();
	void Update();
	void HandleInput();
};
