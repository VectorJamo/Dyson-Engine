#pragma once

int main()
{
	Application* app = new Game();
	app->MainLoop();

	delete app;
}
