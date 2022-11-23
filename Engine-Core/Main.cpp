#include "src/graphics/window.h"
#include "src/error_handling.h"

int main()
{
	ds::graphics::Window window(800, 600, "Dyson Engine");
	if (!window.Init())
		THROW_ERROR("Intialization failed!");
	window.SetVSyncEnabled(true);
	
	while (!window.IsClosed())
	{
		window.Clear(0.0f, 0.0f, 0.0f, 1.0f);
		window.PollEvents();


		

		window.Display();
	}

	return 0;
}