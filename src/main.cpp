#include "config.h"
#include "core/app.h"

int main(){
	std::unique_ptr<App> app = std::make_unique<App>();
	app->run();
	return 0;
}