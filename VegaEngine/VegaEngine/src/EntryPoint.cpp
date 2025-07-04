#include "pch.h"
#include "EntryPoint.h"
#include "Core/System.h"

int main(int argc, char** argv)
{
	auto app = vega::CreateSystem();

	app->Init();
	while (app->IsRunning())
	{
		app->Run();
	}
	app->Release();

	delete app;
	return 0;
}