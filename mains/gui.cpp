#include <app/app.hpp>

int main()
{
	App* app = new App(1920, 1080, "Fractals");
	app->loop();
	delete app;

	return 0;
}