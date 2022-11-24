// The main function(entry point) to be included by every project that uses the Dyson engine
#pragma once

int main()
{
	Application* app = new Application();
	app->Run();
	delete app;
}