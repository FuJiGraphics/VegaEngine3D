#include "pch.h"
#include "EntryPoint.h"

int main(int argc, char** argv)
{
	vega::System* app = vega::CreateSystem();

	app->Init();
	while (app->IsRunning())
	{
		app->Frame();
	}
	app->Release();

	delete app;
	return 0;
}