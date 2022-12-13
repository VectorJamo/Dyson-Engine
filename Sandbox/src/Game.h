#include <application.h>

using namespace ds;
using namespace graphics;
using namespace util;

class Game : public Application
{
private:
	Sprite* blue, *red;

	float blueAngle, redAngle;

public:
	Game();
	~Game();

	void Setup();
	void Update();
	void HandleInput();
};
