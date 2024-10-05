#include "config.h"
#include "core/app.h"

int main(){
	const int width = 800;
	const int height = 600;

	std::unique_ptr<App> app = std::make_unique<App>(width, height, "Jynx");
	app->run();
	return 0;
}