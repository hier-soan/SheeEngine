#include "Application.h"
#include <iostream>

namespace SheeEngine
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{
			std::cout << "Shee Engine Is Running " << std::endl;
		}
	}
}
