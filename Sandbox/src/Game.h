#include <application.h>

using namespace ds;
using namespace graphics;
using namespace util;

class Game : public Application
{
private:
	Sprite* sprite;

	Texture* block, *wall;

public:
	Game();
	~Game();

	void Setup();
	void Update();
	void HandleInput();
};
