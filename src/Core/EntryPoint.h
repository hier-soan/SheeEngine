#pragma once

#ifdef SENGINE_PLATFORM_WINDOWS

extern SheeEngine::Application* SheeEngine::CreateApplication();

int main(int argc, char** argv)
{
	SheeEngine::Log::Init();
	SENGINE_LOG_WARN("SheeEngine Initialize");
	SENGINE_LOG_INFO("Hello SheeEngine");

	auto APP = SheeEngine::CreateApplication();
	APP->Update();
	delete(APP);
}

#endif