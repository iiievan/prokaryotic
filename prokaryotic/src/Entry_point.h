#pragma once

#include <Prokaryotic.h>

#ifdef PRKRTC_PLATFORM_WINDOWS

extern PROKARYOTIC::Application* PROKARYOTIC::Create_application();

int main(int argc, char** argv)
{
	PROKARYOTIC::Log::init();

	LOG_CORE_WARN("Initialized log!");
	LOG_CLIENT_INFO("Hello!");

	auto app = PROKARYOTIC::Create_application();

	app->run();

	delete app;
}
#endif