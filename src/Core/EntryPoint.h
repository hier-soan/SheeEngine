#pragma once
#include "Application.h"

#ifdef SENGINE_PLATFORM_WINDOWS

extern SheeEngine::Application* SheeEngine::CreateApplication();

int main(int argc, char** argv)
{
	auto APP = SheeEngine::CreateApplication();
	APP->Run();
	delete(APP);
}

#endif